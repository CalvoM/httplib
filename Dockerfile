FROM gcc:latest
COPY . /usr/src/my_server
WORKDIR /usr/src/my_server
RUN gcc -g server.c -o server
CMD ["./server","./client"]
EXPOSE 8080
LABEL Name=Chat_Server
