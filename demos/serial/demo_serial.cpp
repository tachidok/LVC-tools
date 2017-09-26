#include <iostream>

// Include common files
#include "../../src/general/common_includes.h"

// The source code in charge of managing serial communications
#include "../../src/serial/cc_serial.h"

using namespace lvc_tools;

int main(int argc, char *argv[])
{
 // Open the file from where we get the data that will be sent through
 // the serial port
 std::ifstream input_file("validate/validate_demo_serial.dat", std::ios_base::in);
 
 // Open a file to output the information for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 // Object to manage the serial communication
 CCSerial serial_communication("Test_communication",
                               "ttyUSB0",
                               115200,
                               SERIAL_N_DATA_BITS::N8BITS,
                               SERIAL_PARITY::NONE,
                               SERIAL_STOP_BITS::ONE);
  
 // Try to establish a connection
 if (!serial_communication.try_to_connect())
  {
   ERROR_MESSAGE("Error establishing communication");
  }
 
 // Read the input file, one line at a time and send them through the
 // serial port
 
 // Maximum number of characters to store in the send buffer
 const unsigned n_send_buffer = 100;
 // Allocate memory for the send buffer
 char *send_buffer = new char[n_send_buffer];
 // Clear the send_buffer
 memset(send_buffer, 0, n_send_buffer);
 
 // Maximum number of characters to store in the receive buffer
 const unsigned n_receive_buffer = 100;
 // Allocate memory for the send buffer
 char *receive_buffer = new char[n_receive_buffer];
 // Clear the receive_buffer
 memset(receive_buffer, 0, n_receive_buffer);
 
 // Loop while there are data in the input file
 while (input_file.getline(send_buffer, 100))
  {
   std::cout << "Send buffer: " << send_buffer << std::endl;
   // -------------
   // Send the data
   // -------------
   if (!serial_communication.send_data(send_buffer, n_send_buffer))
    {
     ERROR_MESSAGE("Error sending data");
    }
   
   // Wait half a second to let the serial port have the data ready
   // for reading
   usleep(5.0e5);
   
   // ---------------------------
   // Receive data
   // ---------------------------
   if (!serial_communication.receive_data(receive_buffer, n_receive_buffer))
    {
     ERROR_MESSAGE("Error receiving data");
    }
   
   std::cout << "Receive buffer: " << receive_buffer << std::endl;
   
   // Add the received data to the output test file
   output_test << receive_buffer << std::endl;
   
   // Clear the sender and receiver buffer
   memset(send_buffer, 0, n_send_buffer);
   memset(receive_buffer, 0, n_receive_buffer);
   
  }
 
 // Close the input file
 input_file.close();
 
 // Close the test/validation file
 output_test.close();
 
 return 0;
 
}

