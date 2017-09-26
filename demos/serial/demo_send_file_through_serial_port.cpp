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
 std::ifstream input_file("validate/serial_send_file.dat", std::ios_base::in | std::ios::binary);
 if (input_file.fail())
  {
   ERROR_MESSAGE("We could not open the file that is sent through the serial port");
  }
 
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
 
 // Store the byte read from the file and send it
 char byte;

 // Loop until eof
 while(!input_file.eof())
  {
   input_file.get(byte);
   
   std::cout << "Send byte: 0x" << std::hex << static_cast<int>(byte) << std::endl;
   // -------------
   // Send the byte
   // -------------
   // Number of bytes to send
   const unsigned n_send_byte = 1;
   if (!serial_communication.send_data(&byte, n_send_byte))
    {
     ERROR_MESSAGE("Error sending data");
    }

   // Delay
   usleep(1.0e3);
   
  }
 
 // Close the input file
 input_file.close();
 
 return 0;
 
}

