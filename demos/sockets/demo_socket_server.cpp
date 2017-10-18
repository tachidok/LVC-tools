#include <iostream>

// Include common files
#include "../../src/general/common_includes.h"

// The source code in charge of managing a server socket
#include "../../src/sockets/cc_socket_server.h"

using namespace lvc_tools;

int main(int argc, char *argv[])
{ 
 // Open a file where we will store the data received from the client
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 const int listening_port = 80000;
 
 // Object to manage the server socket
 CCSocketServer socket_server("My server", "127.0.0.1", listening_port);
 
 // Maximum number of characters to store in the receive buffer
 const unsigned n_receive_buffer = 100;
 // Allocate memory for the send buffer
 char *receive_buffer = new char[n_receive_buffer];
 // Clear the receive_buffer
 memset(receive_buffer, 0, n_receive_buffer);
 
 // Try to start the server
 if (!socket_server.start())
  {
   ERROR_MESSAGE("Error starting the server");
  }
 
 // Loop while there are data in the input file
 while (socket_server.receive(receive_buffer, n_receive_buffer))
  {
   std::cout << "Receive buffer: " << receive_buffer << std::endl;
   
   // Add the received data to the output test file
   output_test << receive_buffer << std::endl;
   
   // Clear buffer
   memset(receive_buffer, 0, n_receive_buffer);
   
  }

 // Stop the server
 socket_server.stop();
 
 // Close the test/validation file
 output_test.close();
 
 return 0;
 
}

