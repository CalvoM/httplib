# http-server in C
## Compile the program
```bash
g++ main.cpp Server/Server.cpp -o main -I Server/
```
## Run the program
```bash 
./main
```
## Using the docker container
### Build
```bash 
docker build -t mwadime/my_net_server .
```
### Run
```bash 
docker run -it -p 8080:8080 mwadime/my_net_server
```

Enjoy!