/**
 * Server test: to test basic listen server function
 * Basic echo server - will send all data back that it recieves
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../sprockets.h"


int main() {
    
    socket_t listen_server;
    if (TCPServer("8000", &listen_server) > 0) {
        printf("Error - couldn't intialize server\n");
        exit(1);
    }

    socket_t client;
    if (TCPClient(listen_server, &client)) {
        printf("Error: couldn't intialize client\n");
        exit(1);
    }

    // Now that we have a listen server and an appropriate client, we wait for data and then send it back
    char buffer[1024];
    unsigned int sent;

    for (;;){
        memset(buffer, 0, 1024);
        sent=0;

        // Stream data in
        printf("waiting on data....\n");
        if (TCPRecv(client, buffer, 1024, &sent)){
            printf("Error, retrying\n");
            continue;
        } else {
            printf("Recieved %d bytes: %.*s \n", sent, sent, buffer);
        }
        
        if (strncmp(buffer, "\\quit", 9) == 0){
            break;
        }

        printf("attempting to send data...\n");
        switch(TCPSend(client, buffer, sent)){
            case NR_OK:
                printf("Sucessfully sent %d bytes!\n", sent);
                break;
            case NR_Failure:
                printf("Error sending data, quitting\n");
                exit(1);
                break;
            default:
                printf("Misc error!\n");
                exit(1);
        }
    }
    
    // Now kill it off
    TCPKill(client);
    TCPKill(listen_server);
}