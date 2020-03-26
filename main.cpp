#include "Server/Server.hpp"
int main(){
    Println("SERVER")
    Server server;
    while(server.get_address()!=0);
    while(server.init_and_bind()==NULL){
        Println("Nothing bound!")
    }
    while(server.listen_for_clients(MAX_CONNECTIONS)!=0);
    while(server.accept_client_connection()==-1);
    int n = server.read_html_page();
    server.prepare_response(n);
    Println("Sent %d bytes",server.send_to_client());
}