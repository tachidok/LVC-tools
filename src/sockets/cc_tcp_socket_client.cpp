#include "cc_tcp_socket_client.h"

namespace lvc_tools
{
 /// ==================================================================
 /// Constructor
 /// ==================================================================
 CCTCPSocketClient::CCTCPSocketClient(std::string client_ID,
                                      std::string server_name,
                                      const int port)
  : ACSocket(client_ID, server_name, port)
 {
    
 }
 
 /// ==================================================================
 /// Destructor
 /// ==================================================================
 CCTCPSocketClient::~CCTCPSocketClient()
 {
  disconnect();
 }
 
 /// ==================================================================
 /// Connects with a server (blocking behaviour)
 /// ==================================================================
 bool CCTCPSocketClient::connect()
 {
  // Check whether the client is already connected
  if (Status == CLIENT_SOCKET_CONNECTED)
   {
    return true;
   }
  
  // Create the socket
  FD = socket(AF_INET, SOCK_STREAM, 0);
  
  if (FD < 0)
   {
    Status = CLIENT_SOCKET_DISCONNECTED;
    return false;
   }
  
  // Structure to store the server name
  struct hostent *server;
  //Get host name
  server = gethostbyname(Server_name.c_str());
  
  if (server == NULL)
   {
    Status = CLIENT_SOCKET_DISCONNECTED;
    close(FD);
    return false;
   }
  
  // Structure to store server connection configuration
  struct sockaddr_in serv_addr;
  // Fill with zeroes
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  // Set the port
  serv_addr.sin_port = htons(Port);
  
  // Connect ... [blocking]
  if (::connect(FD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
   {
    Status = CLIENT_SOCKET_DISCONNECTED;
    close(FD);
    return false;
   }

  // Connection established
  Status = CLIENT_SOCKET_CONNECTED;
  
  std::cout << "Socket CLIENT [" << Client_ID << "] connected" << std::endl;
  
  return true;
  
 }
 
 /// ==================================================================
 /// Disconnect
 /// ==================================================================
 void CCTCPSocketClient::disconnect()
 {
  if (Status == CLIENT_SOCKET_CONNECTED)
   {
    Status = CLIENT_SOCKET_DISCONNECTED;
    if (FD >= 0)
     {
      close(FD);
     }
   }
  
  std::cout << "Socket CLIENT [" << Client_ID << "] disconnected" << std::endl;
  
 }
 
 /// ==================================================================
 /// Send data through the socket
 /// ==================================================================
 int CCTCPSocketClient::send(unsigned char *buffer, const int size)
 {
  // Check that the cient is connected with a server
  if (Status != CLIENT_SOCKET_CONNECTED)
   {
    return -1;
   }
  
  // Send data and get the number of sent data
  return ::write(FD, buffer, size);
 }
 
 /// ==================================================================
 /// Receive data from the socket
 /// ==================================================================
 int CCTCPSocketClient::receive(unsigned char *buffer, const int size)
 {
  // Check that the client is connected with a server
  if (Status != CLIENT_SOCKET_CONNECTED)
   {
    return -1;
   }
  
  // Get the data and the number of received data
  return ::read(FD, buffer, size);
 }

 /// ==================================================================
 /// Send data through the socket
 /// ==================================================================
 int CCTCPSocketClient::send(void *buffer, const int n_send_bytes)
 {
  // Check that the cient is connected with a server
  if (Status != CLIENT_SOCKET_CONNECTED)
   {
    return -1;
   }
  
  // Send data and get the number of sent data
  return ::write(FD, buffer, n_send_bytes);
 }
 
 /// ==================================================================
 /// Receive data from the socket
 /// ==================================================================
 int CCTCPSocketClient::receive(void *buffer, const int n_receive_bytes)
 {
  // Check that the client is connected with a server
  if (Status != CLIENT_SOCKET_CONNECTED)
   {
    return -1;
   }
  
  // Get the data and the number of received data
  return ::read(FD, buffer, n_receive_bytes);
 }

} // namespace lvc_tools
