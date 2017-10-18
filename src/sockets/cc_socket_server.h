#ifndef CC_SOCKET_SERVER_H
#define CC_SOCKET_SERVER_H

#include "../general/common_includes.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

namespace lvc_tools
{
 
 enum Server_socket_status {SERVER_STARTED, SERVER_CONNECTED, SERVER_DISCONNECTED, SERVER_STOPPED};
 
 /// @class CCSocketServer implements a POSIX server for a TCP/IP
 /// connection, currently this class only supports one client TODO:
 /// Support more clients

 class CCSocketServer
 {
 public:
 
  /// Constructor
  CCSocketServer(std::string server_ID, std::string server_name, const int listening_port);
 
  /// Destructor
  ~CCSocketServer();
 
  /// Start the server and waits for incomming connections from clients (blocking)
  bool start();
 
  /// Stop the server
  void stop();
 
  /// Send data through the socket
  int send(unsigned char *buffer, const int size);
 
  /// Receive data from the socket
  int receive(unsigned char *buffer, const int size);

  /// Send binary data through the socket
  int send(void *buffer, const int n_send_bytes);
 
  /// Receive binary data from the socket
  int receive(void *buffer, const int n_receive_bytes);
 
 private:
  
  /// Stores the server ID
  std::string Server_ID;
  
  /// Stores the server name
  std::string Server_name;
  
  /// File descriptor for the server
  int FD_server;

  /// File descriptor for the connected client
  int FD_client;
  
  /// The port where the server is listening for incoming connections
  int Listening_port;
 
  /// Stores the server socket current status
  Server_socket_status Status;
 
 };
 
} // namespace lvc_tools

#endif // CC_SOCKET_SERVER_H
