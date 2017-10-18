#ifndef CCTCPSOCKETCLIENT_H
#define CCTCPSOCKETCLIENT_H

#include "ac_socket.h"

namespace lvc_tools
{
 class CCTCPSocketClient : public virtual ACSocket
 {
 public:
 
  /// Constructor
  CCTCPSocketClient(std::string client_ID, std::string server_name, const int port);
  
  /// Destructor
  virtual ~CCTCPSocketClient();
  
  /// Connects with a server (blocking behaviour)
  bool connect();
  
  /// Disconnect
  void disconnect();
  
  /// Send data through the socket
  int send(unsigned char *buffer, const int size);
  
  /// Receive data from the socket
  int receive(unsigned char *buffer, const int size);
  
  /// Send data through the socket
  int send(void *buffer, const int n_send_bytes);
  
  /// Receive data from the socket
  int receive(void *buffer, const int n_receive_bytes); 
  
 };
 
} // namespace lvc_tools

#endif // CCTCPSOCKETCLIENT_H
