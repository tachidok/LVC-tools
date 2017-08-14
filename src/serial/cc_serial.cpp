// IN THIS FILE: Implementation of a concrete class to communicate
// (send/receive) data through the serial port data.

#include "cc_serial.h"

namespace lvc_tools
{
 
 // ===================================================================
 // Constructor. Opens a serial connection using the given
 // configuration. Give it a name for easy identification in case you
 // have multiple serial connections. If you are in doubt on the
 // configuration just give it a name, a serial port name and the
 // baudrate, we will take care of the rest
 // ===================================================================
 CCSerial::CCSerial(std::string communication_name,
                    std::string port_name, const unsigned baudrate,
                    SERIAL_N_BITS n_data_bits = 8BITS,
                    SERIAL_PARITY Parity = NONE,
                    SERIAL_STOP_BITS n_stop_bits = ONE)
  : Communication_name(communication_name),
    Port_name(port_name),
    Baudrate(baudrate),
    N_data_bits(n_data_bits),
    Parity(Parity),
    N_stop_bits(n_stop_bits)
 {
  // Initialise connection as disconnected
  Communication_status = SERIAL_DISCONNECTED;
 }
  
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class T>
 CCSerial::~CCSerial()
 {
  // Change to disconnected state
  Communication_status = SERIAL_DISCONNECTED;
  
  RS232_CloseComport();
 }

 // ===================================================================
 // Try to establish a connection
 // ===================================================================
 bool CCSerial::try_to_connect()
 {  
  // Get the port number
  const unsigned int port_number = RS232_GetPortnr(Port_name);
  
  // Set the mode
  char mode[3];
  if (N_data_bits == 8BITS)
   {
    mode[0] = '8';
   }
  else if (N_data_bits == 7BITS)
   {
    mode[0] = '7';
   }
  else if (N_data_bits == 6BITS)
   {
    mode[0] = '6';
   }
  else if (N_data_bits == 5BITS)
   {
    mode[0] = '5';
   }
  else
   {
    ostream error_message;
    error_message << "Non supported number of data bits\nYou asked for ["
                  << N_data_bits << "] n data bits, but the supported ones are:\n"
                  << "8BITS, 7BITS, 6BITS and 5BITS data bits\n";
    ERROR_MESSAGE(error_message);
   }

  if (Parity == NONE)
   {
    mode[1] = 'N';
   }
  else if (Parity == EVEN)
   {
    mode[1] = 'E';
   }
  else if (Parity == EVEN)
   {
    mode[1] = 'O';
   }
  else
   {
    ostream error_message;
    error_message << "Non supported parity\nYou asked for ["
                  << Parity << "] parity, but the supported ones are:\n"
                  << "NONE, EVEN or ODD\n";
    ERROR_MESSAGE(error_message);
   }

  if (N_stop_bits == ONE)
   {
    mode[2] = '1';
   }
  else if (N_stop_bits == TWO)
   {
    mode[2] = '2';
   }
  else
   {
    ostream error_message;
    error_message << "Non supported number of stop bits\nYou asked for ["
                  << N_stop_bits << "] n stop bits, but the supported ones are:\n"
                  << "ONE and TWO\n";
    ERROR_MESSAGE(error_message);
   }

  // Try to open the serial port
  if (RS232_OpenComport(port_number, Baudrate, mode))
   {
    return false;
   }
  
  // Change to connected state
  Communication_status = SERIAL_CONNECTED;
  
  return true;
 }
  
}
