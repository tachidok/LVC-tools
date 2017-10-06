#include "cc_socket_server.h"

/// ==================================================================
/// Constructor
/// ==================================================================
CCSocketServer::CCSocketServer(std::string server_name, const int listening_port) 
{
 /// Initiliase file descriptors
 FD_server = -1;
 FD_client = -1;
 
 // Store the name of the server
 Server_name = server_name;
 
 // Sets the listerning port
 Listening_port = listening_port;

 /// Initial status for server
 Status = SERVER_STOPPED;
 
}

/// ==================================================================
/// Destructor
/// ==================================================================
CCSocketServer::~CCSocketServer()
{
 /// Stops the server
 stop();
}

/// ==================================================================
/// Start the server and waits for incomming connections from clients
/// (blocking)
/// ==================================================================
bool CCSocketServer::start()
{
 // A data structure to store client lenght information
 socklen_t client_length;
 
 // Store server and client address information
 struct sockaddr_in server_address; 
 struct sockaddr_in client_address;
 
 //check that the server is not already connected
 if (Status == SERVER_STARTED)
  {
   return false;
  }
 
 // Create a socket
 FD_server = socket(AF_INET, SOCK_STREAM, 0);
 if (FD_server < 0)
  {
   Status = SERVER_STOPPED;
   return false;
  }

 /// Allows the reuse of local addresses when calling bind()
 int allow_reuse = 1;
 if (setsockopt(FD_server, SOL_SOCKET, SO_REUSEADDR, &allow_reuse, sizeof(int))< 0)
  {
   return false; 
  }

 // Fill with zeroes the given structure
 bzero((char *) &server_address, sizeof(server_address));

 // Configure server and indicate listerning port
 server_address.sin_family = AF_INET;
 server_address.sin_addr.s_addr = INADDR_ANY;
 server_address.sin_port = htons(Listening_port);
 
 // Bind the socket to an port in the local machine using the bind()
 // system call.
 if (bind(FD_server, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
  {
   Status = SERVER_STOPPED;
   close(FD_server);
   return false;
  }
  
 // Start listening for connections using the listen() system call
 listen(FD_server, 1);
 
 // Set the status to started
 Status = SERVER_STARTED;
 
 std::cout << "Socket Server [" << Server_name << "] started and listening ..." << std::endl;
 
 // Prepare to accept a client
 client_length = sizeof(client_address);
 
 // Accept an incomming client connection using the accept() system call.
 FD_client = accept(FD_server, (struct sockaddr *) &client_address, &client_length);
 
 if (FD_client < 0)
  {
   Status = SERVER_STOPPED;
   close(FD_server);
   return false;
  }
 
 Status = SERVER_CONNECTED;
 
 std::cout << "Socket Server [" << Server_name << "] connected" << std::endl;
 
 return true;

}

/// ==================================================================
/// Stop the server
/// ==================================================================
void CCSocketServer::stop()
{
 if (Status == SERVER_CONNECTED)
  {
   Status = SERVER_DISCONNECTED; 
   
   if (FD_client >= 0)
    {
     close(FD_client);
    }
   
   Status = SERVER_STOPPED;
   
   if (FD_server >= 0)
    {
     close(FD_server);
    }
  }
 
}

/// ==================================================================
/// Send data through the socket
/// ==================================================================
int CCSocketServer::send(unsigned char *buffer, const int size)
{
 // Check that the server is connected with a client
 if (Status != SERVER_CONNECTED)
  {
   return -1;
  }

 // Send data and get the number of sent data
 return ::write(FD_client, buffer, size);
 
}

/// ==================================================================
/// Receive data from the socket
/// ==================================================================
int CCSocketServer::read(unsigned char *buffer, const int size)
{
 // Check that the server is connected with a client
 if (Status != SERVER_CONNECTED)
  {
   return -1;
  }
 
 // Get the data and the number of received data
 return ::read(FD_client, buffer, size);
 
}

/// ==================================================================
/// Send binary data through the socket
/// ==================================================================
int CCSocketServer::send(void *buffer, const int size)
{
 // Check that the server is connected with a client
 if (Status != SERVER_CONNECTED)
  {
   return -1;
  }

 // Send data and get the number of sent data
 return ::write(FD_client, buffer, size);
 
}

/// ==================================================================
/// Receive binary data from the socket
/// ==================================================================
int CCSocketServer::read(void *buffer, const int size)
{
 // Check that the server is connected with a client
 if (Status != SERVER_CONNECTED)
  {
   return -1;
  }
 
 // Get the data and the number of received data
 return ::read(FD_client, buffer, size);
 
}
