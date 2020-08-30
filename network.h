/* network.h
 * This provides a handy useful interface for socket programming
*/


#ifndef  NETWORK_LIB_H
#define  NETWORK_LIB_H 

typedef int socket_t;

typedef enum {
    NR_OK,        // For when a function worked fine  
    NR_Disconect, //For when a connection is disconnected
    NR_BadAddress, // For when an address is badly formmated
    NR_BadArguement, // For when the arguements passed to a function are illegal. NR_BadAdddress should be used if it fits bietter
    NR_No_Data, // For if a socket has no data to be sent

    NR_Failure = 32 /*Generic Failure*/
} NetResult; 

/** TCPServer
 * Creates a new socket that's set up to act as a server ala bind(), accept()*
 */
NetResult TCPServer(const char* port, socket_t* out);
/* TODO Blocking. Will get a new client socket placed in out
*/
NetResult TCPClient(socket_t server, socket_t* out);

/*Initiates a client connection to (address, port) into out
 * Either address or port can be null, both raises an error
 * address set to null sets it to loopback, port unknown
*/
NetResult TCPConnect(const char* address, const char* port, socket_t* out);

/*Pushes all of the bytes up to len in payload into the connection*/
NetResult TCPSend(socket_t socket, char* payload, unsigned int len);
/*Gets the data from the connection and pushes it into out out
 * TODO whether or not I should have a *len variable clobbers 
*/
NetResult TCPRecv(socket_t socket, char* out, unsigned int len);

/*Kills the connection*/
NetResult TCPKill(socket_t socket);
#endif
