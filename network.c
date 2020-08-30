/* network.c
 * implementation of network.h
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>


#include "network.h"

NetResult TCPServer(const char* port, socket_t* out){
    struct addrinfo hints; // hints for getaddrinfo()
    struct addrinfo* servinfo; // pointer to results

    metset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /*TODO - check for error, iterate over *servinfo for appropriate deets*/
    if (getaddrinfo(NULL, port, &hints, &servinfo) != 0) {
        return NR_Failure; /*TODO proper error handling*/   
    }

    socket_t server;
    struct addrinfo* ptr;
    for (ptr = servinfo; ptr != NULL; ptr = ptr->ai_next) {
        // Check to see if we can both initialize a socket of the appropriate protocol, and bind it to our chose protocol/adddress
        if (server = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol) == -1) continue;
        if (bind(server, ptr->ai_addr, ptr->ai_addrlen) == -1) continue;

        //If we have no issue, then we break out
        break;
    }
    // If we iterated through the list completely and didn't break out early on a good info bit, then quit
    if (ptr == NULL){
        return NR_Failure;
    }
    // If listen cannot be setup, quit
    if (listen(server, 10) == -1) return NR_Failure;

    freeaddrinfo(servinfo);

    *out = server;
    return NR_OK;
}

NetResult TCPClient(socket_t server, socket_t* out) {
    // TODO may add debug info using these
    socket_t client = accept(server, NULL, NULL);
    if (client == -1) {
        //TODO better error checking
        return NR_Failure;
    }
    else {
        *out = client;
        return NR_OK;
    }
}

NetResult TCPConnect(const char* address, const char* port, socket_t* out) {
    struct addrinfo hints;
    struct addrinfo* info;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if (getaddrinfo(address, port, &hints, &info) != 0){
        return NR_Failure;
    }
    
    socket_t connection;
    struct addrinfo* ptr;
    for(ptr = info; ptr != NULL; ptr = ptr->ai_next) {
        //First initialize a socket
        if (connection = 
            socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol) 
        == -1){
            continue;
        } 
        // If we are unable to connect using this protocol, close it and try again
        if (connect(connection, ptr->ai_addr, ptr->ai_addrlen) == -1){
            close(connection);
            continue;
        }

        // If all goes well, break
        break;
    }

    if (ptr == NULL) {
        return NR_Failure;
    }

    freeaddrinfo(info);
    *out = connection;
    return NR_OK;
}

NetResult TCPSend(socket_t socket, char* payload, unsigned int len){
    int remaing = len;
    int position = 0;
    char* buffer = payload;
    /*send all of the data*/
    while (remaing > 0) {
        int result = send(socket, (void*) buffer, remaing,0);

        if (result == -1) {
            return NR_Failure;
        }

        remaing -= result;
        position += result;
        buffer = &buffer[position];
    }

    return NR_OK;
}

NetResult TCPRecv(socket_t socket, char* out, unsigned int len) {
    int position = 0;

    while (position != len) {
        int result = recv(socket, &out[position], len - position, 0);
        
        if (result == -1) {
            return NR_No_Data;
        }
        
        if (result == 0) {
            return NR_Disconect;
        }

        position += result;
    }

    return NR_OK;
}