#ifndef AC_SOCKET_H
#define AC_SOCKET_H

#include "../general/common_includes.h"

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

namespace lvc_tools
{

 enum Client_socket_status {CLIENT_SOCKET_CONNECTED, CLIENT_SOCKET_DISCONNECTED};

 /// @class ACSocket is an abstract class that implements the interface
 /// of the Server and Client socket classes

 class ACSocket
 {
 public:
  
  /// Constructor
  ACSocket(std::string client_name, std::string server_to_connect_name, const int port);
  
  /// Destructor
  virtual ~ACSocket();
  
  /// Connects (blocking behaviour, calls "try_to_connect()" until success)
  virtual bool connect() = 0;
  
  /// Tries to connect
  virtual bool try_to_connect() = 0;
 
  /// Disconnect
  virtual void disconnect() = 0;
 
  /// Send data through the socket
  virtual int send(unsigned char *buffer, const int size) = 0;
 
  /// Receive data from the socket
  virtual int receive(unsigned char *buffer, const int size) = 0;
  
  /// Send data through the socket
  virtual int send(void *buffer, const int size) = 0;
 
  /// Receive data from the socket
  virtual int receive(void *buffer, const int size) = 0;
  
 protected:

  /// Stores the client name
  string Client_name;
  
  /// The host/server to connect name
  string Server_to_connect_name;
  
  /// A file descriptor
  int FD;
  
  /// The port to connect the socket
  int Port;
 
  /// Stores the socket current status
  Client_socket_status Status;  
  
 };

} // namespace lvc_tools
 
#endif // AC_SOCKET_H
