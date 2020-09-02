#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../sprockets.h"


int main() {
    socket_t listen_server;
    if (TCPServer("8000", &listen_server)) {
        printf("oh noes an error!\n");
        exit(0);
    }

    socket_t client;
    if (TCPClient(listen_server, &client)){
        printf("couldn't establish client connection");
        exit(0);
    }

    char buffer[1024];
    int recieved = 0;

    for(;;){
        
    }
}