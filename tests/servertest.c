/**
 * Server test: to test basic listen server function
 * Basic echo server - will send all data back that it recieves
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"


int main(int argc, char* argv) {
    
    socket_t listen_server;
    if (TCPServer("8000", &listen_server) > 0) {
        printf("Error - couldn't intialize server");
        exit(1);
    }

    socket_t client;
    if (TCPClient(listen_server, &client) > 0) {
        printf("Error: couldn't intialize client");
        exit(1);
    }
    // Now that we have a listen server and an appropriate client, we wait for data and then send it back
    char buffer[1024];
    int recieved;
    loop:
    for (;;){
        memset(buffer, 0, 1024);
        
        // Stream data in
        switch(TCPRecv(client, buffer, 1024)){
            case NR_Disconect:
                printf("Client disconnected! ending server");
                exit(1);
                break;
            case NR_No_Data:
                continue; // retry
            default:
                prtinf("Recieved ");
        }


    }
}