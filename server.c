#include "global.h"
int read_html_page(){
    FILE *webPage = fopen("index.html","r");
    if(webPage==NULL) return -1;
    int size=0;
    while(!feof(webPage)){
        char c = fgetc(webPage);
        html_body[size] = c;
        size++;
    }
    return size;
}
void prepare_response(int html_size){
    int n = sprintf(tmp_buff,"HTTP/1.0 200 OK\r\n");
    tmp_buff+=n;
    n = sprintf(tmp_buff, "Content-Type: text/html; charset=UTF-8\r\n");
    tmp_buff+=n;
    n = sprintf(tmp_buff, "Content-Length: %d\r\n",html_size);
    tmp_buff+=n;
    n = sprintf(tmp_buff, "Accept-Ranges: bytes\r\n");
    tmp_buff+=n;
    n = sprintf(tmp_buff, "Connection: close\r\n\r\n");
    tmp_buff+=n;
    n = sprintf(tmp_buff,"%s",html_body);
    tmp_buff=0;
}
int main(int argc,char* argv[]){
    Println("Server starting")
  struct addrinfo filler, *serverInfo, *addrs;
  struct sockaddr_storage clientInfo;
  char ip_str[INET6_ADDRSTRLEN];
  // autofill the filler data
  memset(&filler, 0, sizeof filler);
  filler.ai_family = AF_UNSPEC;
  filler.ai_socktype = SOCK_STREAM;
  filler.ai_flags = AI_PASSIVE;
  int status;
  if ((status = getaddrinfo(NULL, PORT_NUM, &filler, &serverInfo)) != 0) {
    Println("(getaddrinfo) Error") 
    exit(EXIT_FAILURE);
  }
  int serverId,clientId;
  for(addrs=serverInfo;addrs!=NULL;addrs=addrs->ai_next){
        serverId = socket(addrs->ai_family,addrs->ai_socktype,addrs->ai_protocol);
        if(serverId==-1)continue;
        Println("Socket Init OK")
        if(bind(serverId,addrs->ai_addr,addrs->ai_addrlen)==0){
            Println("Binding OK")
            break;
        }
        close(serverId);
    }
    if(addrs==NULL){
        Println("Nothing Bound")
        exit(EXIT_FAILURE);
    }
    if(listen(serverId,MAX_CONNECTIONS)!=0){
        Println("Error Listening")
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(serverInfo);
    socklen_t addrsize = sizeof clientInfo;
    clientId = accept(serverId,(struct sockaddr*)&clientInfo,&addrsize);
    if(clientId==-1){
        Println("Error in accepting")
        exit(EXIT_FAILURE);
    }
    inet_ntop(clientInfo.ss_family,get_in_addr((struct sockaddr*)&clientInfo),ip_str,sizeof ip_str);
    Println("Connection from %s\n\r\n\r",ip_str)
    int recv_size;
    int html_size=0;
    char recv_buff[102400];
    bool once=true;
    while(1){
        if((recv_size = recv(clientId,recv_buff,sizeof recv_buff,0))!=1 && once){
            recv_buff[recv_size] = 0;
            Println("%s",recv_buff)
            html_size=read_html_page();
            prepare_response(html_size);
            int n = send(clientId,http_response,strlen(http_response),0);
            Println("Sent package of size:%d",n)
            once=false;
        }
    }
    
}