#include <arpa/inet.h>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include "httpd/httpd_tcp.h"
#include "message/message.h"

HTTPD_TCP::HTTPD_TCP(const std::string &log_path, const std::string &html_path, const uint16_t port,
                     const uint16_t transaction_port, const unsigned int backlog)
    : m_log_path(log_path)
    , m_html_path(html_path)
    , m_port(port)
    , m_transaction_port(transaction_port)
    , m_backlog(backlog)
{
    std::ofstream log_file(m_log_path, std::ios::out | std::ios::app);
    if (!log_file.is_open())
    {
        throw std::runtime_error("Failed to open log file: " + m_log_path);
    }
    log_file.close();
}

HTTPD_TCP::~HTTPD_TCP()
{
    if (m_socket != -1 || m_port != 0)
    {
        closeSocket();
    }
}

void HTTPD_TCP::run()
{
    writeLog("HTTPD_TCP starts running");
    console();
    writeLog("HTTPD_TCP has terminated");
}

void HTTPD_TCP::writeLog(const std::string &message) const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::ofstream log_file(m_log_path, std::ios::out | std::ios::app);
    if (!log_file.is_open())
    {
        throw std::runtime_error("Failed to open log file: " + m_log_path);
    }

    std::time_t now = std::time(nullptr);
    char        time_str[100];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    log_file << "[" << time_str << "] " << message << '\n';

    log_file.close();
}

void HTTPD_TCP::console()
{
    while (true)
    {
        std::cout << "-------------------------------------------\n";
        std::cout << "| Command List:                           |\n";
        std::cout << "| 1. start        - Start the server      |\n";
        std::cout << "| 2. stop         - Stop the server       |\n";
        std::cout << "| 3. exit         - Exit the console      |\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "Enter command: ";

        std::string command;
        std::cin >> command;

        if (command == "start")
        {
            std::cout << "Starting server on port " << m_port << "...\n";
            initSocket(m_port);
            m_state = SERVING;
            std::thread listenThread(&HTTPD_TCP::listen, this, m_backlog);
            listenThread.detach();
        }
        else if (command == "stop")
        {
            std::cout << "Stopping server on port " << m_port << "...\n";
            m_state = NOT_SERVING;
            closeSocket();
        }
        else if (command == "exit")
        {
            std::cout << "Exiting console...\n";
            m_state = NOT_SERVING;
            closeSocket();
            break;
        }
        else
        {
            std::cout << "Unknown command. Please try again.\n";
        }
    }
}

void HTTPD_TCP::initSocket(const uint16_t port)
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to set SO_REUSEADDR: " + std::string(strerror(errno)));
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to bind socket on port " + std::to_string(port));
    }

    m_socket = serverSocket;

    char serverIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(serverAddress.sin_addr), serverIP, INET_ADDRSTRLEN);
    std::string logMessage = "Socket initialized on IP: " + std::string(serverIP) +
                             ", Port: " + std::to_string(ntohs(serverAddress.sin_port)) +
                             ", fd=" + std::to_string(m_socket);
    writeLog(logMessage);
}

void HTTPD_TCP::listen(const unsigned int backlog) const
{
    if (m_socket == -1)
    {
        throw std::runtime_error("Socket is not initialized");
    }

    if (::listen(m_socket, backlog) == -1)
    {
        close(m_socket);
        writeLog("Failed to listen");
        throw std::runtime_error("Failed to listen: " + std::string(strerror(errno)));
    }

    sockaddr_in clientAddress{};
    socklen_t   clientAddressLength = sizeof(clientAddress);
    while (m_state == SERVING)
    {
        int clientSocket = accept(m_socket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (clientSocket == -1)
        {
            close(m_socket);
            writeLog("Failed to accept connection");
            throw std::runtime_error("Failed to accept connection");
        }

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
        std::string logMessage = "Accepted connection from client IP: " + std::string(clientIP);
        writeLog(logMessage);

        std::thread clientThread(&HTTPD_TCP::handleClient, this, clientSocket);
        clientThread.detach();
    }
}

void HTTPD_TCP::closeSocket()
{
    if (m_socket != -1)
    {
        close(m_socket);
        writeLog("Socket closed on port " + std::to_string(m_port) + ", fd=" + std::to_string(m_socket));
        m_socket = -1;
    }
}

void HTTPD_TCP::handleClient(const int clientSocket) const
{
    char    buffer[4096];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0)
    {
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';

    std::string request(buffer);
    writeLog("[Request]\n" + request);

    std::istringstream iss(request);
    std::string        method, path, protocol;
    iss >> method >> path >> protocol;

    std::string body;
    size_t      headerEnd = request.find("\r\n\r\n");
    if (headerEnd == std::string::npos) headerEnd = request.find("\n\n");
    if (headerEnd != std::string::npos)
    {
        body = request.substr(headerEnd + 4);
    }

    try
    {
        if (method == "GET")
        {
            if (path == "/messages")
            {
                Message reqMsg;
                reqMsg.insert("assignment", "read");
                reqMsg.insert("index", "7"); 
                std::string respData = communicateWithAnotherProcess(reqMsg.to_str());
                // writeLog("[Response] GET /messages:\n" + respData);
                sendJSONResponse(clientSocket, 200, respData);
            }
            else
            {
                std::string   filePath = path == "/" ? m_html_path : path;
                std::ifstream file(filePath);
                if (file.good())
                {
                    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    sendHTMLResponse(clientSocket, 200, content);
                }
                else
                {
                    sendErrorResponse(clientSocket, 404, "File not found");
                }
            }
        }
        else if (method == "POST" && path == "/messages")
        {
            Message reqMsg;
            reqMsg.read(body);
            reqMsg.insert("assignment", "write");
            std::string respData = communicateWithAnotherProcess(reqMsg.to_str());
            writeLog("[Response] POST /messages write:\n" + respData);
            sendJSONResponse(clientSocket, 200, respData);
        }
        else
        {
            sendErrorResponse(clientSocket, 405, "Method Not Allowed");
        }
    }
    catch (const std::exception &e)
    {
        Message errMsg;
        errMsg.insert("error", e.what());
        sendJSONResponse(clientSocket, 400, errMsg.to_str());
        writeLog("[Error] " + std::string(e.what()));
    }

    close(clientSocket);
}

std::string HTTPD_TCP::communicateWithAnotherProcess(const std::string &message) const
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(m_transaction_port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        close(sockfd);
        writeLog("Failed to connect to another process");
        throw std::runtime_error("Failed to connect to another process");
    }

    ssize_t bytesSent = send(sockfd, message.c_str(), message.size(), 0);
    if (bytesSent == -1)
    {
        close(sockfd);
        writeLog("Failed to send message to another process");
        throw std::runtime_error("Failed to send message to another process");
    }

    char    buffer[4096];
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1)
    {
        close(sockfd);
        writeLog("Failed to receive response from another process");
        throw std::runtime_error("Failed to receive response from another process");
    }
    buffer[bytesRead] = '\0';

    close(sockfd);
    return std::string(buffer);
}

void HTTPD_TCP::sendJSONResponse(const int clientSocket, const int code, const std::string &data) const
{
    std::string response = "HTTP/1.1 " + std::to_string(code) +
                           " OK\r\n"
                           "Content-Type: application/json\r\n"
                           "Content-Length: " +
                           std::to_string(data.size()) +
                           "\r\n"
                           "\r\n" +
                           data;
    send(clientSocket, response.c_str(), response.size(), 0);
}

void HTTPD_TCP::sendHTMLResponse(const int clientSocket, const int code, const std::string &content) const
{
    std::string response = "HTTP/1.1 " + std::to_string(code) +
                           " OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: " +
                           std::to_string(content.size()) +
                           "\r\n"
                           "\r\n" +
                           content;
    send(clientSocket, response.c_str(), response.size(), 0);
}

void HTTPD_TCP::sendErrorResponse(const int clientSocket, const int code, const std::string &msg) const
{
    std::string response = "HTTP/1.1 " + std::to_string(code) + " " + msg +
                           "\r\n"
                           "Content-Length: 0\r\n\r\n";
    send(clientSocket, response.c_str(), response.size(), 0);
}