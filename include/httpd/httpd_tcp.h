#ifndef HTTPD_TCP_H
#define HTTPD_TCP_H

#include <mutex>
#include <stdint.h>
#include <string>

#define NOT_SERVING 0
#define SERVING 1

class HTTPD_TCP
{
  public:
    /**
     * @brief HTTPD_TCP 构造函数
     *
     * 该构造函数用于初始化HTTP服务器实例，配置日志路径、HTML资源路径、监听端口以及事务处理端口。
     *
     * @param log_path         日志文件的存储路径，用于记录服务器运行时的日志信息。
     * @param html_path        HTML资源的根目录路径，服务器将从此路径加载静态文件（如HTML、CSS、JS）。
     * @param m_port           HTTP服务器监听的端口号，用于接收客户端的HTTP请求。
     * @param transaction_port 事务处理模块的端口号，用于与事务处理模块进行通信（如进程间通信）。
     * @param backlog          监听队列的最大长度，默认值为7，表示最多允许7个连接请求排队等待处理。
     *
     * @note 该构造函数会初始化服务器的基本配置，但不会启动服务器。需调用其他成员函数（如`start()`）来启动服务。
     *
     * @example
     * HTTPD_TCP server("./logs", "./html", 7001, 7002);
     * server.start();
     */
    HTTPD_TCP(const std::string &log_path, const std::string &html_path, const uint16_t m_port,
              const uint16_t transaction_port, const unsigned int backlog = 7);
    ~HTTPD_TCP();

    /**
     * @brief 启动服务器并打开控制台
     *
     * @note 在调用此函数之前，请确保已正确初始化服务器（如通过构造函数配置端口和路径）。
     *       该函数会阻塞当前线程，直到服务器被关闭或程序终止。
     *
     * @example
     * HTTPD_TCP server("./logs", "./html", 8080, 9090);
     * server.run(); // 启动服务器并打开控制台
     */
    void run();

  private:
    void        writeLog(const std::string &message) const;
    void        console();
    void        initSocket(const uint16_t port);
    void        listen(const unsigned int backlog) const;
    void        closeSocket();
    void        handleClient(const int clientSocket) const;
    std::string communicateWithAnotherProcess(const std::string &message) const;

    void sendJSONResponse(const int clientSocket, const int code, const std::string &data) const;
    void sendHTMLResponse(const int clientSocket, const int code, const std::string &content) const;
    void sendErrorResponse(const int clientSocket, const int code, const std::string &msg) const;

  private:
    std::string        m_log_path;
    std::string        m_html_path;
    uint16_t           m_port;
    uint16_t           m_transaction_port;
    unsigned int       m_backlog;
    int                m_socket = -1;
    short int          m_state  = NOT_SERVING;
    mutable std::mutex m_mutex;
};

#endif // !HTTPD_TCP_H
