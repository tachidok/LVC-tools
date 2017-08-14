// IN THIS FILE: The definition of a class to communicate
// (send/receive) data through a serial port

// Check whether the class has been already defined
#ifndef CCSERIAL_H
#define CCSERIAL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

// Include the external package for serial communication
#include "../../external_src/serial_rs-232/rs232.h"

namespace lvc_tools
{
 
 // Enumerator to indicate whether the connection has been established
 // or not
 enum SERIAL_STATUS {SERIAL_CONNECTED, SERIAL_DISCONNECTED};
 // Enumerators to pass supported values to the serial port configuration
 enum SERIAL_N_DATA_BITS {8BITS, 7BITS, 6BITS, 5BITS};
 enum SERIAL_PARITY {NONE, EVEN, ODD};
 enum SERIAL_STOP_BITS {ONE, TWO};
 
 /// @class CCSerial cc_serial.h
 
 // Concrete class to represent a serial communication
 class CCSerial
 {
  
 public:
  
  // Constructor. Opens a serial connection using the given
  // configuration. Give it a name for easy identification in case you
  // have multiple serial connections. If you are in doubt on the
  // configuration just give it a name, a serial port name and the
  // baudrate, we will take care of the rest
  CCSerial(std::string communication_name,
           std::string port_name, const unsigned baudrate,
           SERIAL_N_BITS n_data_bits = 8BITS,
           SERIAL_PARITY parity = NONE,
           SERIAL_STOP_BITS n_stop_bits = ONE);
  
  // Copy constructor
  CCSerial(const CCSerial &copy)
   {
    ERROR_MESSAGE("Undefined behaviour for copy constructor");
   }
  
  // Assignment operator
  CCSerial &operator=(const CCSerial &copy)
   {
    ERROR_MESSAGE("Undefined behaviour for operator '='");
   }
  
  // Destructor
  ~CCSerial();
  
  // Try to establish a connection
  bool try_to_connect();
  
  // Send data
  const int send_data(const unsigned char *data, const unsigned n_send_data);
  
  // Receive data in buffer
  const int receive_data(const unsigned char *buffer, const unsigned n_receive_data);
  
  // Get the communication name
  inline std::string communication_name() {return Communication_name;}
  
  // Get the port name
  inline std::string port_name() {return Port_name;}
  
  // Get the baudrate
  inline int baudrate() {return Baudrate;}
  
  // Get the number of data bits
  inline SERIAL_N_BITS n_data_bits() {return N_data_bits;}

  // Get the parity
  inline SERIAL_PARITY parity() {return Parity;}

  // Get the number of stop bits
  inline SERIAL_STOP_BITS n_stop_bits() {return N_stop_bits;}
  
  // Get the serial communication status
  inline SERIAL_STATUS communication_status() {return Communication_status;}
  
 protected:
  
  // Serial communication name
  std::string Communication_name;
  
  // Serial communication configuration port name
  std::string Port_name;
  
  // Serial communication configuration baudrate
  const int Baudrate;
  
  // Serial communication configuration number of data bits
  SERIAL_N_BITS N_data_bits;
  
  // Serial communication configuration parity
  SERIAL_PARITY Parity;
  
  // Serial communication configuration number of stop bits
  SERIAL_STOP_BITS N_stop_bits;
  
  // Serial communication status
  SERIAL_STATUS Communication_status;
  
 };
 
}

#endif // #ifndef CCDATA_TPL_H
