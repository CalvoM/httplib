#include "Server.hpp"
Server::Server(){
    memset(&filler,0,sizeof filler);
    filler.ai_family = AF_UNSPEC;
    filler.ai_socktype = SOCK_STREAM;
    filler.ai_flags = AI_PASSIVE;
}
/**
 * @brief: get addresses from the filler
*/
uint8_t Server::get_address(){
  return getaddrinfo(NULL, PORT_NUM, &filler, &serverInfo);
}
/**
 * @brief: init_and bind addrs
*/
struct addrinfo* Server::init_and_bind(){
    for(addrs=serverInfo;addrs!=NULL;addrs=addrs->ai_next){
    serverId = socket(addrs->ai_family,addrs->ai_socktype,addrs->ai_protocol);
    Println("%d",serverId)
    if(serverId==-1)continue;
    Println("Socket Init OK")
    if(bind(serverId,addrs->ai_addr,addrs->ai_addrlen)==0){
        Println("Binding OK")
        break;
    }
    // close(serverId);
    }
    Println("---")
    return addrs;
}
uint8_t Server::listen_for_clients(int max_connections){
    return listen(serverId,max_connections);
}
int Server::accept_client_connection(){
    freeaddrinfo(serverInfo);
  socklen_t addrsize = sizeof clientInfo;
  clientId = accept(serverId,(struct sockaddr*)&clientInfo,&addrsize);
  if(clientId!=-1){
      inet_ntop(clientInfo.ss_family,get_in_addr((struct sockaddr*)&clientInfo),ipStr,sizeof ipStr);
      Println("Connection from %s\n\r\n\r",ipStr)
  }
  Println("%d",clientId)
  return clientId;
}
int Server::read_html_page() {
    Println("Reading")
  FILE* webPage = fopen("./index.html", "r");
  if (webPage == NULL) return -1;
  int size = 0;
  while (!feof(webPage)) {
    char c = fgetc(webPage);
    html_body[size] = c;
    Println("%c",c)
    size++;
  }
  return size;
}
void Server::prepare_response(int html_size) {
  int n = sprintf(tmp_buff, "HTTP/1.0 200 OK\r\n");
  tmp_buff += n;
  n = sprintf(tmp_buff, "Content-Type: text/html; charset=UTF-8\r\n");
  tmp_buff += n;
  n = sprintf(tmp_buff, "Content-Length: %d\r\n", html_size);
  tmp_buff += n;
  n = sprintf(tmp_buff, "Accept-Ranges: bytes\r\n");
  tmp_buff += n;
  n = sprintf(tmp_buff, "Connection: close\r\n\r\n");
  tmp_buff += n;
  n = sprintf(tmp_buff, "%s", html_body);
  tmp_buff = 0;
}
int Server::receive_from_client(){
    return recv(clientId,recv_buff,sizeof recv_buff,0);
}
int Server::send_to_client(){
  return send(clientId, http_response, strlen(http_response), 0);
}
Server::~Server(){
}