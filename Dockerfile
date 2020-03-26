FROM gcc:latest
COPY . /usr/src/my_server
WORKDIR /usr/src/my_server
RUN g++ main.cpp Server/Server.cpp -o main -I Server/
CMD ["./main"]
EXPOSE 8080
LABEL Name=Chat_Server
