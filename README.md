# http-server in C
## Compile the program
```bash
gcc server.c -o server
```
## Run the program
```bash 
./server
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