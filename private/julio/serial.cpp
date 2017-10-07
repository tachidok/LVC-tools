#include <iostream>

// Include common files
#include "../../src/general/common_includes.h"

// The source code in charge of managing serial communications
#include "../../src/serial/cc_serial.h"

using namespace lvc_tools;

int main(int argc, char *argv[])
{ 
 // Open a file to output the information for testing/validation
 std::ofstream output_file("output.dat", std::ios_base::out);
 
 // Object to manage the serial communication
 CCSerial serial_communication("Test_communication",
                               "ttyUSB0",
                               9600,
                               SERIAL_N_DATA_BITS::N8BITS,
                               SERIAL_PARITY::NONE,
                               SERIAL_STOP_BITS::ONE);
  
 // Try to establish a connection
 if (!serial_communication.try_to_connect())
  {
   ERROR_MESSAGE("Error establishing communication");
  }
 
 // Maximum number of characters to store in the receive buffer
 const unsigned n_receive_buffer = 100;
 // Allocate memory for the send buffer
 char *receive_buffer = new char[n_receive_buffer];
 // Clear the receive_buffer
 memset(receive_buffer, 0, n_receive_buffer); 
 
 bool LOOP = true;
 // Loop while there are data in the input file
 while (LOOP)
  {   
   // Wait
   //usleep(5.0e5);
   usleep(1.0e5);
   
   // ---------------------------
   // Receive data
   // ---------------------------
   if (!serial_communication.receive(receive_buffer, n_receive_buffer))
    {
     ERROR_MESSAGE("Error receiving data");
    }
   
   //std::cout << std::showbase << std::hex << receive_buffer << std::endl;
   std::cout << receive_buffer << std::endl;
   
   // Add the received data to the output test file
   output_file << receive_buffer << std::endl;
   
   // Clear the sender and receiver buffer
   memset(receive_buffer, 0, n_receive_buffer);
   
  }
  
  // Close the test/validation file
 output_file.close();
 
 return 0;
 
}

