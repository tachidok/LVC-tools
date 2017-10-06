#include "ac_socket.h"

namespace lvc_tools
{

 /// ==================================================================
 /// Constructor
 /// ==================================================================
 ACSocket::ACSocket(std::string client_name,
                    std::string server_to_connect_name,
                    const int port)
 { 
  // Store the name of the client
  Client_name = client_name;
  
  // Copy the server to connect
  Server_to_connect_name = server_to_connect_name;
  
  /// Initialise the file descriptor
  FD = 0;
  
  /// The default port
  Port = port;
  
  /// Initialise as disconnected
  Status = CLIENT_SOCKET_DISCONNECTED;
  
 }
 
 /// ==================================================================
 /// Destructor
 /// ==================================================================
 ACSocket::~ACSocket()
 { }

} // namespace lvc_tools
