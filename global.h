#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT_NUM "8080"
#define HTML_SIZE 102400
#define HEADER_SIZE 512
#define RESPONSE_SIZE 102912
#define MAX_CONNECTIONS 5
#define Println(...)       \
  {                        \
    do {                   \
      printf(">>> ");      \
      printf(__VA_ARGS__); \
      printf("\r\n");      \
    } while (0);           \
  }
void *get_in_addr(struct sockaddr *sa) {
  return sa->sa_family == AF_INET
             ? (void *)&(((struct sockaddr_in *)sa)->sin_addr)
             : (void *)&(((struct sockaddr_in6 *)sa)->sin6_addr);
}
char html_body[HTML_SIZE];
char http_response[RESPONSE_SIZE];
char http_response_previous[RESPONSE_SIZE];
char* tmp_buff = http_response;
#endif  