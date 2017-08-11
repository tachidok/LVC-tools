#ifndef CCCOMMUNICATIONSERIAL_H
#define CCCOMMUNICATIONSERIAL_H

#include "CACommunicationInterface.h"
#include "Common/CCConfigFile.h"

#include "Report/CCReport.h"

using namespace std;

#define NOPARITY 0 // Sin paridad: 0
#define EVENPARITY 1 // Paridad par: 1
#define ODDPARITY 2 //  Paridad impar: 2
#define STOPBIT 1
#define TWO_STOPBIT 2

#define HARDWARE_FLOW 1
#define SOFTWARE_FLOW 2
#define NO_FLOW 3

#define CANONICAL_INPUT 1
#define RAW_INPUT 2

#define NO_CUSTOM_INPUT 0
#define CUSTOM_CANONICA 1
#define CUSTOM_RAW 2

class CCCommunicationSerial : public virtual CACommunicationInterface
{
public:
    CCCommunicationSerial(const string &_configFile, const string &classname);
    ~CCCommunicationSerial();

    void initialization(const string &_configFile, const string &classname);//Configurar el serial
    bool openCommunication(); //Abrir la conexion
    void closeCommunication(); //cerrar la conexion
    void reconnect(); //Cerrar y volver a abrir la conexion
    int write(unsigned char *_buffer, int size); //Enviar datos
    int read(unsigned char *_buffer, int size); //Recibir datos

protected:

    string serial_port;//!< Nombre del puerto que se desea abrir. i.e, "/dev/ser1"
    speed_t speed;//!< velocidad [in] Velocidad a la que se debe abrir el puerto.
    short stop_bits;//!< Número de bits de parada. Los valores posibles son 1 y 2.
    short parity;//!< Especifica el tipo de paridad utilizado. Los valores posibles son EVENPARITY, ODDPARITY, NOPARITY
    short data_bits;//!< Número de bits de datos (5,6,7,8)
    short flow_control;//!< Especifica el tipo de control de flujo a utilizar. Los valores posibles son HARDWARE_FLOW, SOFTWARE_FLOW, NO_FLOW

    short type_input;//!< Entrada canonica 1, entrada raw 2
    short custom_input; //!< 0. entrada ninguna, 1. entrada canonica, 2. entrada en bruto (raw)
    short min_num; //!< Minimo numero de caracteres a leer (en caso de entrada raw)
    short time_out;//!< Tiempo para esperar a los datos (decimas de segundo)

    struct termios options_old;

};


#endif // CCCOMMUNICATIONSERIAL_H
