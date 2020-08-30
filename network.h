/* network.h
 * This provides a handy useful interface for socket programming
*/


#ifndef  NETWORK_LIB_H
#define  NETWORK_LIB_H 

typedef int socket_t;
//wooo
typedef enum {
    NR_OK,              // For when a function worked fine  
    NR_Disconect,       // For when a connection is disconnected
    NR_BadAddress,      // For when an address is badly formmated
    NR_BadArguement,    // For when the arguements passed to a function are illegal. NR_BadAdddress should be used if it fits bietter
    NR_No_Data,         // For if a socket has no data to be sent
    NR_Failure = 32     /*Generic Failure. This is a sign a function needs to be further developed*/
} NetResult; 

/** TCPServer()
 * Create and initialize a socket to be used as a listening server, use TCPClient() to get new client connections for use
 * 
 * port (char*):  string of service name or numeric port number server should be running on
 * out (socket_t*):  out paramter new socket will be stored into
 * 
 * Returns NetResult: TODO error code for function call
 */
NetResult TCPServer(const char* port, socket_t* out);

/** TCPClient()
 *  equivalent to acept() call, accepts a listening socket and stores new connection in out
 * 
 * server (socket_t): listening socket, initialized with TCPServer() or listen(), to listen for new connections on
 * out (socket_t*): socket to store new client connection socket in
 * 
 * Returns NetResult: TODO error code
*/
NetResult TCPClient(socket_t server, socket_t* out);

/** TCPConnect()
 * Initiates a client connection to (address, port) into out
 * 
 * address (const char*): internet address to connect to
 *  TODO behavior for null
 * port (const char*): common service name or port number to connect to
 * out (socket_t*): location for new socket to be stored in
 * 
 * Returns NetResult: TODO error code for function call
*/
NetResult TCPConnect(const char* address, const char* port, socket_t* out);

/**
 * Sends up to len bytes of the data in payload, does not need to recalled to send all of the data
 * 
 * socket (socket_t): socket to stream data over
 * payload(char*): buffer of data to be sent
 * len (unsigned int): ammount of data to be sent
 *  TODO behavior on zero
 * 
 * Returns NetResult: TODO
*/
NetResult TCPSend(socket_t socket, char* payload, unsigned int len);
/*Gets the data from the connection and pushes it into out out
 * TODO  
*/
NetResult TCPRecv(socket_t socket, char* out, unsigned int len, unsigned int* recieved);

/*Kills the connection*/
NetResult TCPKill(socket_t socket);
#endif
