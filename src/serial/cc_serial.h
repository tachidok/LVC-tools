// IN THIS FILE: The definition of a class to communicate
// (send/receive) data through a serial port

// Check whether the class has been already defined
#ifndef CCSERIAL_H
#define CCSERIAL_H

#include "../general/common_includes.h"

// Include the external package for serial communication
#include "../../external_src/serial_rs-232/rs232.h"

namespace lvc_tools
{
 
 // Enumerator to indicate whether the connection has been established
 // or not
 enum class SERIAL_STATUS {SERIAL_CONNECTED, SERIAL_DISCONNECTED};
 // Enumerators to pass supported values to the serial port configuration
 enum class SERIAL_N_DATA_BITS {N8BITS, N7BITS, N6BITS, N5BITS};
 enum class SERIAL_PARITY {NONE, EVEN, ODD};
 enum class SERIAL_STOP_BITS {ONE, TWO};
 
 /// @class CCSerial cc_serial.h
 
 // Concrete class to represent a serial communication
 class CCSerial
 {
  
 public:
  
  // Constructor. Opens a serial connection using the given
  // configuration. Give it a name for easy identification in case you
  // have multiple serial connections. If you are in doubt on the
  // configuration just give it a name, a serial port name and the
  // baudrate, we will take care of the rest. The port name does not
  // require the "/dev/" substring, it is automatically appened to the
  // given port name)
  CCSerial(const char *communication_name,
           const char *port_name, const unsigned baudrate,
           SERIAL_N_DATA_BITS n_data_bits = SERIAL_N_DATA_BITS::N8BITS,
           SERIAL_PARITY parity = SERIAL_PARITY::NONE,
           SERIAL_STOP_BITS n_stop_bits = SERIAL_STOP_BITS::ONE);
  
  // Copy constructor
  CCSerial(const CCSerial &copy)
   : Baudrate(0)
   {
    ERROR_MESSAGE("Undefined behaviour for copy constructor");
   }
  
  // Assignment operator
  CCSerial &operator=(const CCSerial &copy)
   {
    ERROR_MESSAGE("Undefined behaviour for operator '='");
    return *this;
   }
  
  // Destructor
  ~CCSerial();
  
  // Try to establish a connection
  bool try_to_connect();
  
  // Disconnects
  void disconnect();
  
  // Send data (returns the number of sent data)
  const int send_data(unsigned char *send_buffer, const unsigned n_send_buffer);
  
  // Receive data in buffer (returns the number of read data)
  const int receive_data(unsigned char *receive_buffer, const unsigned n_receive_buffer);

  // Send binary data (returns the number of sent data)
  const int send_data(void *send_buffer, const unsigned n_send_buffer);
  
  // Receive binary data in buffer (return the number of read data)
  const int receive_data(void *receive_buffer, const unsigned n_receive_buffer);
  
  // Get the communication name
  inline const char* communication_name() {return Communication_name;}
  
  // Get the port name
  inline const char* port_name() {return Port_name;}
  
  // Get the baudrate
  inline int baudrate() {return Baudrate;}
  
  // Get the number of data bits
  inline SERIAL_N_DATA_BITS n_data_bits() {return N_data_bits;}
  
  // Get the parity
  inline SERIAL_PARITY parity() {return Parity;}

  // Get the number of stop bits
  inline SERIAL_STOP_BITS n_stop_bits() {return N_stop_bits;}
  
  // Get the serial communication status
  inline SERIAL_STATUS communication_status() {return Communication_status;}
  
 protected:
  
  // Serial communication name
  const char* Communication_name;
  
  // Serial communication configuration port name
  const char* Port_name;
  
  // Serial communication configuration baudrate
  const int Baudrate;
  
  // Serial communication configuration number of data bits
  SERIAL_N_DATA_BITS N_data_bits;
  
  // Serial communication configuration parity
  SERIAL_PARITY Parity;
  
  // Serial communication configuration number of stop bits
  SERIAL_STOP_BITS N_stop_bits;
  
  // Serial communication status
  SERIAL_STATUS Communication_status;

 private:
  
  // Automatically computed from the Port_name
  int Port_number;
  
 };
 
} // namespace lvc_tools

#endif // #ifndef CCDATA_TPL_H
