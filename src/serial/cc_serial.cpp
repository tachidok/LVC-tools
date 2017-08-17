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
 CCSerial::CCSerial(const char* communication_name,
                    const char* port_name, const unsigned baudrate,
                    SERIAL_N_DATA_BITS n_data_bits,
                    SERIAL_PARITY Parity,
                    SERIAL_STOP_BITS n_stop_bits)
  : Communication_name(communication_name),
    Port_name(port_name), 
    Baudrate(baudrate),
    N_data_bits(n_data_bits),
    Parity(Parity),
    N_stop_bits(n_stop_bits)
 {
  // Compute the port number
  Port_number = RS232_GetPortnr(Port_name);
  
  // Initialise connection as disconnected
  Communication_status = SERIAL_STATUS::SERIAL_DISCONNECTED;
 }
  
 // ===================================================================
 // Destructor
 // ===================================================================
 CCSerial::~CCSerial()
 {
  // Performs a disconnection
  disconnect();
 }
 
 // ===================================================================
 // Try to establish a connection
 // ===================================================================
 bool CCSerial::try_to_connect()
 {
  // Set the mode
  char *mode = new char[3];
  if (N_data_bits == SERIAL_N_DATA_BITS::N8BITS)
   {
    mode[0] = '8';
   }
  else if (N_data_bits == SERIAL_N_DATA_BITS::N7BITS)
   {
    mode[0] = '7';
   }
  else if (N_data_bits == SERIAL_N_DATA_BITS::N6BITS)
   {
    mode[0] = '6';
   }
  else if (N_data_bits == SERIAL_N_DATA_BITS::N5BITS)
   {
    mode[0] = '5';
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Non supported number of data bits\nYou asked for ["
                  << static_cast<int>(N_data_bits) << "] n data bits, but the supported ones are:\n"
                  << "N8BITS, N7BITS, N6BITS and N5BITS data bits\n";
    ERROR_MESSAGE(error_message);
   }

  if (Parity == SERIAL_PARITY::NONE)
   {
    mode[1] = 'N';
   }
  else if (Parity == SERIAL_PARITY::EVEN)
   {
    mode[1] = 'E';
   }
  else if (Parity == SERIAL_PARITY::EVEN)
   {
    mode[1] = 'O';
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Non supported parity\nYou asked for ["
                  << static_cast<int>(Parity) << "] parity, but the supported ones are:\n"
                  << "NONE, EVEN or ODD\n";
    ERROR_MESSAGE(error_message);
   }

  if (N_stop_bits == SERIAL_STOP_BITS::ONE)
   {
    mode[2] = '1';
   }
  else if (N_stop_bits == SERIAL_STOP_BITS::TWO)
   {
    mode[2] = '2';
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Non supported number of stop bits\nYou asked for ["
                  << static_cast<int>(N_stop_bits) << "] n stop bits, but the supported ones are:\n"
                  << "ONE and TWO\n";
    ERROR_MESSAGE(error_message);
   }
  
  // Try to open the serial port
  if (RS232_OpenComport(Port_number, Baudrate, mode))
   {
    return false;
   }
  
  std::cout << "Serial communication established ["<< Communication_name << "]" << std::endl;
  
  // Change to connected state
  Communication_status = SERIAL_STATUS::SERIAL_CONNECTED;
  
  return true;
 }

 // ===================================================================
 // Disconnects
 // ===================================================================
 void CCSerial::disconnect()
 {
  if (Communication_status != SERIAL_STATUS::SERIAL_DISCONNECTED)
   {
    // Change to disconnected state
    Communication_status = SERIAL_STATUS::SERIAL_DISCONNECTED;
    
    RS232_CloseComport(Port_number);
   }
  
  std::cout << "Serial communication disconnected ["<< Communication_name << "]\n";
  
 }
 
 // ===================================================================
 // Send data
 // ===================================================================
 const int CCSerial::send_data(unsigned char *send_buffer,
                               const unsigned n_send_buffer)
 {
  // Check that the connection has been established
  if (Communication_status != SERIAL_STATUS::SERIAL_CONNECTED)
   {
    return -1;
   }
  
  // Send data
  int iret = RS232_SendBuf(Port_number, send_buffer, n_send_buffer);
  if (iret)
   {
    return false;
   }
  else
   {
    return true;
   }
  
 }
 
 // ===================================================================
 // Receive data in buffer (return the number of read data)
 // ===================================================================
 const int CCSerial::receive_data(unsigned char *receive_buffer,
                                  const unsigned n_receive_buffer)
 {
  // Check // TODO: hat the connection has been established
  if (Communication_status != SERIAL_STATUS::SERIAL_CONNECTED)
   {
    return -1;
   }
  
  // Receive data
  return RS232_PollComport(Port_number, receive_buffer, n_receive_buffer);
 }
 
} // namespace lvc_tools
