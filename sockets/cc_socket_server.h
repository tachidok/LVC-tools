#ifndef CC_SOCKET_SERVER_H
#define CC_SOCKET_SERVER_H

#include <string>
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

enum Server_socket_status {SERVER_INITIALISED, SERVER_LISTENING, SERVER_STOPPED};

/// @class CCSocketServer implements a POSIX server for a TCP/IP
/// connection, currently this class only supports one client TODO:
/// Support more clients

class CCSocketServer
{
 public:
 
 /// Constructor
 CCSocketServer(const int listening_port);
 
 /// Destructor
 ~CCSocketServer();
 
 /// Initiliase the server and let it ready to lister for client connections
 bool initialise();
 
 /// Listen for clients trying to connect (blocking until a client gets connected)
 bool listen();
 
 /// Stop the server
 void stop();
 
 /// Send data through the socket
 int send(unsigned char *buffer, const int size);
 
 /// Receive data from the socket
 int receive(unsigned char *buffer, const int size);
 
 private:
 
 /// File descriptor for the server
 int FD_server;

 /// File descriptor for the connected client
 int FD_client;
  
 /// The port where the server is listening for incoming connections
 int Listening_port;
 
 /// Stores the server socket current status
 Server_socket_status Status;
 
};

#endif // CC_SOCKET_SERVER_H
