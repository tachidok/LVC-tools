#ifndef CCTCPSOCKETCLIENT_H
#define CCTCPSOCKETCLIENT_H

#include "ac_socket.h"

namespace lvc_tools
{
 class CCTCPSocketClient : public virtual ACSocket
 {
 public:
 
  /// Constructor
  CCTCPSocketClient(std::string client_name, std::string server_to_connect_name, const int port);
  
  /// Destructor
  virtual ~CCTCPSocketClient();
  
  /// Connects (blocking behaviour, calls "try_to_connect()" until success)
  bool connect();
 
  /// Tries to connect
  bool try_to_connect();
  
  /// Disconnect
  void disconnect();
  
  /// Send data through the socket
  int send(unsigned char *buffer, const int size);
  
  /// Receive data from the socket
  int receive(unsigned char *buffer, const int size);
  
  /// Send data through the socket
  int send(void *buffer, const int size);
  
  /// Receive data from the socket
  int receive(void *buffer, const int size); 
  
 };
 
} // namespace lvc_tools

#endif // CCTCPSOCKETCLIENT_H
