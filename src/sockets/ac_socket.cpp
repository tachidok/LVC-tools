#include "ac_socket.h"

namespace lvc_tools
{

 /// ==================================================================
 /// Constructor
 /// ==================================================================
 ACSocket::ACSocket(std::string client_ID,
                    std::string server_name,
                    const int port)
 { 
  // Store the name of the client
  Client_ID = client_ID;
  
  // Copy the server to connect
  Server_name = server_name;
  
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
