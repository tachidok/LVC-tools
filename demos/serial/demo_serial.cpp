#include <iostream>

// Include common files
#include "../../src/general/common_includes.h"

// The source code in charge of managing serial communications
#include "../../src/serial/cc_serial.h"

using namespace lvc_tools;

int main(int argc, char *argv[])
{ 
 // Object to manage the serial communication
 CCSerial serial_communication("Test_communication",
                               "/dev/ttyUSB00",
                               115200,
                               SERIAL_N_DATA_BITS::N8BITS,
                               SERIAL_PARITY::NONE,
                               SERIAL_STOP_BITS::ONE);
 
 // Try to establish a connection
 if (!serial_communication.try_to_connect())
  {
   ERROR_MESSAGE("Error establishing communication");
  }

 // ---------------------------
 // Send data
 // ---------------------------
 // Data buffer to be send through the serial communication
 //const unsigned char *send_buffer = {"This is a message sent throught the serial communication\n"};
 const unsigned n_send_buffer = 57;
 unsigned char *send_buffer = new unsigned char[n_send_buffer];
 
 // Send the data
 if (!serial_communication.send_data(static_cast<unsigned char*>(send_buffer), n_send_buffer))
  {
   ERROR_MESSAGE("Error sending data");
  }

  // ---------------------------
  // Receive data
  // ---------------------------
  const unsigned n_receive_buffer = 100;
  unsigned char *receive_buffer = new unsigned char[n_receive_buffer];
  memset(receive_buffer, 0, n_receive_buffer);

  if (!serial_communication.receive_data(receive_buffer, n_receive_buffer))
 {
  ERROR_MESSAGE("Error receiving data");
 }
 
 return 0;
 
}

