#include <iostream>

// Include common files
#include "../../src/general/common_includes.h"

// The source code in charge of managing a client socket
#include "../../src/sockets/cc_tcp_socket_client.h"

using namespace lvc_tools;

int main(int argc, char *argv[])
{

 // Open the file from where we get the data that will be sent through
 // the serial port
 std::ifstream input_file("validate/validate_demo_socket_server_client.dat", std::ios_base::in);
 if (input_file.fail())
  {
   ERROR_MESSAGE("We could not open the file that will be sent through sockets");
  } 
 
 const int port = 80000;
 
 // Create the socket client
 
 // Read the input file, one line at a time and send them through the
 // serial port
 CCTCPSocketClient socket_client("My client", "127.0.0.1", port);

 // Maximum number of characters to store in the send buffer
 const unsigned n_send_buffer = 100;
 // Allocate memory for the send buffer
 char *send_buffer = new char[n_send_buffer];
 // Clear the send_buffer
 memset(send_buffer, 0, n_send_buffer);
 
 // Try to connect with a server
 if (!socket_client.connect())
  {
   ERROR_MESSAGE("Error connecting with a server");
  }
 
 // Loop while there are data in the input file
 while (input_file.getline(send_buffer, n_send_buffer))
  {
   // -------------
   // Send the data
   // -------------
   if (!socket_client.send(send_buffer, n_send_buffer))
    {
     ERROR_MESSAGE("Error sending data");
    }
   
   std::cout << "Send buffer: " << send_buffer << std::endl;
   
   // Wait half a second to let the socket have data ready for reading
   usleep(5.0e5); 
   
   // Clear the sender and receiver buffer
   memset(send_buffer, 0, n_send_buffer);
   
  }
 
 // Close the connection
 socket_client.disconnect();
 
 // Close the input file
 input_file.close(); 
 
 return 0;
 
}

