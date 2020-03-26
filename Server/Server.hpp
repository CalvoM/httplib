#ifndef SERVER_H_
#define SERVER_H_
#include "../global.h"
enum class SERVER_ERROR{
    ERROR=-1,
    OK=0
};
class Server{
public:
    Server();
    uint8_t get_address();
    struct addrinfo* init_and_bind();
    uint8_t listen_for_clients(int max_connections);
    int accept_client_connection();
    int read_html_page();
    void prepare_response(int html_size);
    int receive_from_client();
    int send_to_client();
    ~Server();
private:
    const char* PORT_NUM = "8080";
    struct addrinfo filler;
    struct addrinfo *serverInfo;
    struct addrinfo *addrs;
    struct sockaddr_storage clientInfo;
    char ipStr[INET6_ADDRSTRLEN];
    int serverId;
    int clientId;
    int recv_size;
    int html_size = 0;
    char recv_buff[102400];
    char html_body[HTML_SIZE];
    char http_response[RESPONSE_SIZE];
    char http_response_previous[RESPONSE_SIZE];
    char *tmp_buff = http_response;
};
#endif
