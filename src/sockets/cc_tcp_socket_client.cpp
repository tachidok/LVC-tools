#include "cc_tcp_socket_client.h"

namespace lvc_tools
{
 /// ==================================================================
 /// Constructor
 /// ==================================================================
 CCTCPSocketClient(std::string client_name,
                   std::string server_to_connect_name,
                   const int port)
  : ACSocket(client_name, server_to_connect_name, port)
 {
    
 }
 
 /// ==================================================================
 /// Destructor
 /// ==================================================================
 CCTCPSocketClient::~CCTCPSocketClient()
 { }

 /// Destructor
 virtual ~CCTCPSocketClient();

 /// ==================================================================
 /// Connects (blocking behaviour, calls "try_to_connect()" until success)
 /// ==================================================================
 bool CCTCPSocketClient::connect()
 {
  // Check whether the client is already connected
  if (Status == CLIENT_SOCKET_CONNECTED)
   {
    return true;
   }

  // If not connnect then open a socket
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  // Open the socket
  
  //used address the internet domain and stream sockets treat communications as a continuous stream of characters
  FD = socket(AF_INET, SOCK_STREAM, 0);

  if (fd < 0) {
   status = CI_DISCONNECTED;
   report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening socket");
   return false;
  }

  //Get host name
  server = gethostbyname(host_name.c_str());

  if (server == NULL) {
   status = CI_DISCONNECTED;
   close(fd);
   report.errorMessage(string(__PRETTY_FUNCTION__) + ": Host not found");
   return false;
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

  serv_addr.sin_port = htons(port);

  //printf("Cliente: Solicitar conexion\n");

  if (connect(fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
   status = CI_DISCONNECTED;
   close(fd);
   //report.errorMessage(string(__PRETTY_FUNCTION__) + ": The client could not connect");
   return false;
  }

  status = CI_CONNECTED;

  return true;
  
 }

 /// ==================================================================
 /// Tries to connect
 /// ==================================================================
 bool CCTCPSocketClient::try_to_connect()
 {
  
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
 int CCTCPSocketClient::send(void *buffer, const int size)
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
 int CCTCPSocketClient::receive(void *buffer, const int size)
 {
  // Check that the client is connected with a server
  if (Status != CLIENT_SOCKET_CONNECTED)
   {
    return -1;
   }
  
  // Get the data and the number of received data
  return ::read(FD, buffer, size);
 }

} // namespace lvc_tools

bool CCCommunicationClient::openCommunication()
{

 struct sockaddr_in serv_addr;
 struct hostent *server;

 //check that  is not already connected
 if (status == CI_CONNECTED){
  //report.warningMessage(string(__PRETTY_FUNCTION__) + ": already connected");
  return true;
 }

 // Open socket
 //used address the internet domain and stream sockets treat communications as a continuous stream of characters
 fd = socket(AF_INET, SOCK_STREAM, 0);

 if (fd < 0) {
  status = CI_DISCONNECTED;
  report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening socket");
  return false;
 }

 //Get host name
 server = gethostbyname(host_name.c_str());

 if (server == NULL) {
  status = CI_DISCONNECTED;
  close(fd);
  report.errorMessage(string(__PRETTY_FUNCTION__) + ": Host not found");
  return false;
 }

 bzero((char *) &serv_addr, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

 serv_addr.sin_port = htons(port);

 //printf("Cliente: Solicitar conexion\n");

 if (connect(fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
  status = CI_DISCONNECTED;
  close(fd);
  //report.errorMessage(string(__PRETTY_FUNCTION__) + ": The client could not connect");
  return false;
 }

 status = CI_CONNECTED;

 return true;

}

void CCCommunicationClient::reconnect()
{
 closeCommunication();
 openCommunication();
}


