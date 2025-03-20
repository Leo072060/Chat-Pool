#include "message/message.h"
#include "transaction/chatPool/chatPool.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

void handleAI(ChatPool& chatPool) {
    chatPool.AI();
}
std::string handleTransaction(const std::string &request, ChatPool &chatPool)
{
    Message requestMsg;
    requestMsg.read(request);
    requestMsg.print();
    if (!requestMsg.contain("assignment"))
    {
        Message errorMsg;
        errorMsg.insert("error", "Missing 'assignment' key in request.");
        return errorMsg.to_str();
    }

    std::string assignment = requestMsg.get("assignment");
    if (assignment == "write")
    {
        if (!requestMsg.contain("content") || !requestMsg.contain("timestamp"))
        {
            Message errorMsg;
            errorMsg.insert("error", "Missing 'content' or 'timestamp' key for write operation.");
            return errorMsg.to_str();
        }

        Message messageToWrite;
        messageToWrite.insert("content", requestMsg.get("content"));
        messageToWrite.insert("timestamp", requestMsg.get("timestamp"));
        messageToWrite.insert("userId", requestMsg.get("userId"));
        chatPool.storeMessage(messageToWrite);
        Message responseMsg;
        responseMsg.insert("status", "success");
        responseMsg.insert("message", "Message stored successfully.");

        // deal AI
        std::string              content      = requestMsg.get("content");
        bool                     shouldCallAI = false;
        std::vector<std::string> keywords     = {"小雯", "AI", "ai"};
        for (const auto &keyword : keywords)
        {
            if (content.find(keyword) != std::string::npos)
            {
                shouldCallAI = true;
                break;
            }
        }
        if (shouldCallAI)
        {
            std::thread aiThread(handleAI, std::ref(chatPool));
            aiThread.detach(); 
        }

        return responseMsg.to_str();
    }
    else if (assignment == "read")
    {
        if (!requestMsg.contain("index"))
        {
            Message errorMsg;
            errorMsg.insert("error", "Missing 'index' key for read operation.");
            return errorMsg.to_str();
        }

        unsigned int         index    = std::stoul(requestMsg.get("index"));
        std::vector<Message> readMsgs = chatPool.readRecentMessages(5);
        return Message::assemble(readMsgs);
    }
    else
    {
        Message errorMsg;
        errorMsg.insert("error", "Invalid assignment value. Expected 'write' or 'read'.");
        return errorMsg.to_str();
    }
}

int main()
{
    // ******* Parameters *******
    const int port = 7002;
    // **************************

    int                serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t          clientAddressLength = sizeof(clientAddress);
    char               buffer[1024]        = {0};
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(serverSocket, 5) == -1)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to listen on socket");
    }

    std::cout << "Server is running on port " << port << "..." << std::endl;

    ChatPool chatPool("./chatPool/chatPool.db", "python3 ./AI/xiaowen.py");

    while (true)
    {
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength)) == -1)
        {
            throw std::runtime_error("Failed to accept client connection");
        }

        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1)
        {
            close(clientSocket);
            throw std::runtime_error("Failed to read from client");
        }

        std::string request(buffer, bytesRead);
        std::string response = handleTransaction(request, chatPool);

        if (write(clientSocket, response.c_str(), response.size()) == -1)
        {
            close(clientSocket);
            throw std::runtime_error("Failed to send response to client");
        }

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}