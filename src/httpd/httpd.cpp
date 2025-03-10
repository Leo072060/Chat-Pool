#include"httpd/httpd_tcp.h"

int main()
{
    HTTPD_TCP httpd_tcp("./httpd/log_tcp","./httpd/index.html",7001,7002,7);
    httpd_tcp.run();
    return 0;
}