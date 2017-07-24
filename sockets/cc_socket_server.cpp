#include "cc_socket_server.h"

/// ==================================================================
/// Constructor
/// ==================================================================
CCSocketServer::CCSocketServer(const int listening_port) 
{
 /// Initiliase file descriptors
 FD_server = -1;
 FD_client = -1;
 
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

bool CCSocketServer::initialise()
{
 //// HERE HERE HERE HERE
 
 socklen_t clilen;
 struct sockaddr_in serv_addr, cli_addr;
    
 //check that  is not already connected
 if (status == CI_CONNECTED){
  //report.warningMessage(string(__PRETTY_FUNCTION__) + ": already connected");
  return true;
 }

 //Create a socket with the socket() system call
 fd = socket(AF_INET, SOCK_STREAM, 0);

 if (fd < 0) {
  status = CI_DISCONNECTED;
  report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening socket");
  return false;
 }

 int enable=1;
 if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))< 0)
  report.errorMessage("SO_REUSE");

 bzero((char *) &serv_addr, sizeof(serv_addr));

 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(port);

#ifdef GOMEZ_MESSAGES
 fprintf (stderr, "%d\n", port);
#endif // #ifdef GOMEZ_MESSAGES
 //Bind the socket to an address using the bind() system call.
 //For a server socket on the Internet, an address consists of a port number on the host machine.
 if (bind(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
  status = CI_DISCONNECTED;
  close(fd);
  report.errorMessage(string(__PRETTY_FUNCTION__) + ": Failed  to bind an address to the socket server ");
  return false;
 }

 //Listen for connections with the listen() system call
 listen(fd, 1);
 status = CI_CONNECTING;

 clilen = sizeof(cli_addr);

 //Accept a connection with the accept() system call.
 //This call typically blocks until a client connects with the server.
 newSockFd = accept(fd, (struct sockaddr *) &cli_addr, &clilen);

 if (newSockFd < 0) {
  status = CI_DISCONNECTED;
  close(fd);
  report.errorMessage(string(__PRETTY_FUNCTION__) + ": Could not create client socket in the server");
  return false;
 }

 status = CI_CONNECTED;

 return true;

}

void CCSocketServer::closeCommunication()
{
 if (status == CI_CONNECTED)  {
  status = CI_DISCONNECTED;

  if (newSockFd >= 0)
   close(newSockFd);

  if (fd >= 0)
   close(fd);
 }
}

void CCSocketServer::reconnect()
{
 closeCommunication();
 openCommunication();
}

int CCSocketServer::write(unsigned char *_buffer, int size)
{

 if (status != CI_CONNECTED) {
  //report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected socket");
  return -1;
 }

 int n = ::write(newSockFd, _buffer, size);

 if (n < 0)
  closeCommunication();

 return n;
    
}

int CCSocketServer::read(unsigned char *_buffer, int size)
{

 if (status != CI_CONNECTED) {
  //report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected socket");
  return -1;
 }

 int n = ::read(newSockFd, _buffer, size);

 if (n < 0)
  closeCommunication();

 return n;
    
}
