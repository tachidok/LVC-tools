#include "ac_socket.h"

/// ==================================================================
/// Constructor
/// ==================================================================
ACSocket::ACSocket()
{
 /// Initialise the file descriptor
 FD = 0;
  
 /// The default port
 Port = 0;
 
 /// Initialise as disconnected
 Status = CLIENT_SOCKET_DISCONNECTED;
 
}

/// ==================================================================
/// Destructor
/// ==================================================================
ACSocket::~ACSocket()
{ }
