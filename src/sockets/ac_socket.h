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
  ACSocket(std::string client_ID, std::string server_name, const int port);
  
  /// Destructor
  virtual ~ACSocket();
  
  /// Connects with a server (blocking behaviour)
  virtual bool connect() = 0;
  
  /// Disconnect
  virtual void disconnect() = 0;
 
  /// Send data through the socket
  virtual int send(unsigned char *buffer, const int size) = 0;
 
  /// Receive data from the socket
  virtual int receive(unsigned char *buffer, const int size) = 0;
  
  /// Send data through the socket
  virtual int send(void *buffer, const int n_send_bytes) = 0;
 
  /// Receive data from the socket
  virtual int receive(void *buffer, const int n_receive_bytes) = 0;
  
 protected:

  /// Stores the client ID
  std::string Client_ID;
  
  /// The host/server to connect name
  std::string Server_name;
  
  /// A file descriptor
  int FD;
  
  /// The port to connect the socket
  int Port;
 
  /// Stores the socket current status
  Client_socket_status Status;  
  
 };

} // namespace lvc_tools
 
#endif // AC_SOCKET_H
