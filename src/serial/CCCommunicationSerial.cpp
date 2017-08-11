#include "CCCommunicationSerial.h"

extern CCReport report;
extern CCMonitor monitor;

CCCommunicationSerial::CCCommunicationSerial(const string &_configFile, const string &classname)
{
    report.updateMessageRecord(string(__PRETTY_FUNCTION__));
    initialization(_configFile, classname);
}

CCCommunicationSerial::~CCCommunicationSerial()
{

    report.updateMessageRecord(string(__PRETTY_FUNCTION__));

    /* restore the old port settings */
    //tcsetattr(fd,TCSANOW,&options_old); //TODO: No deja desplegar la terminal en linux al aplicar delete al objeto

}

void CCCommunicationSerial::initialization(const string &_configFile, const string &classname)
{

    fd = -1;
    status = CI_DISCONNECTED;

    CCConfigFile cfg(_configFile);

    serial_port = cfg.getValueOfString(classname +".serial_port");
    speed = cfg.getValueOfInt(classname +".speed");
    stop_bits = cfg.getValueOfInt(classname +".stop_bits");
    data_bits = cfg.getValueOfInt(classname +".data_bits");
    parity = cfg.getValueOfInt(classname +".parity");
    flow_control = cfg.getValueOfInt(classname +".flow_control");
    type_input = cfg.getValueOfInt(classname +".type_input");
    min_num = cfg.getValueOfInt(classname +".min_num");
    time_out = cfg.getValueOfInt(classname +".time_out");
    custom_input = cfg.getValueOfInt(classname +".custom_input");

}

bool CCCommunicationSerial::openCommunication()
{

    int iret;
    struct termios options;

    //check that  is not already connected
    if (status == CI_CONNECTED){
        report.warningMessage(string(__PRETTY_FUNCTION__) + ": already connected");
        return true;
    }

    fd = open(serial_port.c_str(), O_RDWR | O_NOCTTY);

    if (fd < 0) {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening port");
        return false;
    }

    bzero(&options, sizeof(options)); /* clear struct for new port settings */

    if (tcgetattr(fd, &options) != 0){
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": tcgetattr() failed");
        return false;
    }

    // Save old tty parameters
    bzero(&options_old, sizeof(options_old)); /* clear struct for new port settings */
    options_old = options;

    switch (speed) {
#ifdef B0
    case 0:
        speed = B0;
        break;
#endif
#ifdef B50
    case 50:
        speed = B50;
        break;
#endif
#ifdef B75
    case 75:
        speed = B75;
        break;
#endif
#ifdef B110
    case 110:
        speed = B110;
        break;
#endif
#ifdef B134
    case 134:
        speed = B134;
        break;
#endif
#ifdef B150
    case 150:
        speed = B150;
        break;
#endif
#ifdef B200
    case 200:
        speed = B200;
        break;
#endif
#ifdef B300
    case 300:
        speed = B300;
        break;
#endif
#ifdef B600
    case 600:
        speed = B600;
        break;
#endif
#ifdef B1200
    case 1200:
        speed = B1200;
        break;
#endif
#ifdef B1800
    case 1800:
        speed = B1800;
        break;
#endif
#ifdef B2400
    case 2400:
        speed = B2400;
        break;
#endif
#ifdef B4800
    case 4800:
        speed = B4800;
        break;
#endif
#ifdef B9600
    case 9600:
        speed = B9600;
        break;
#endif
#ifdef B19200
    case 19200:
        speed = B19200;
        break;
#endif
#ifdef B38400
    case 38400:
        speed = B38400;
        break;
#endif
#ifdef B57600
    case 57600:
        speed = B57600;
        break;
#endif
#ifdef B76800
    case B76800:
        speed = B76800;
        break;
#endif
#ifdef B115200
    case B115200:
        speed = B115200;
        break;
#endif
    default:
        speed = B0;
        break;
    }

    //establecer la velocidad de lectura y escritura
    iret = cfsetispeed(&options, speed); //establecer la velocidad de lectura
    if (iret == 0){ //no hubo error
        iret = cfsetospeed(&options, speed); //establecer la velocidad de escritura
        if (iret != 0){ //ocurrio algun error al configurar la velocidad de escritura
            status = CI_DISCONNECTED;
            close(fd);
            report.errorMessage(string(__PRETTY_FUNCTION__) + ": Error al configurar la velocidad de escritura");
            return false;
        }
    }
    else{ //ocurrio algun error al configurar la velocidad de lectura
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": Error al configurar la velocidad de lectura");
        return false;
    }

    options.c_cflag |= CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    switch(data_bits){
    case 5://5 bits
        options.c_cflag  &= ~CS6;
        options.c_cflag  &= ~CS7;
        options.c_cflag  &= ~CS8;
        options.c_cflag |= CS5;
        break;
    case 6://6 bits
        options.c_cflag  &= ~CS5;
        options.c_cflag  &= ~CS7;
        options.c_cflag  &= ~CS8;
        options.c_cflag |= CS6;
        break;
    case 7://7 bits
        options.c_cflag  &= ~CS5;
        options.c_cflag  &= ~CS6;
        options.c_cflag  &= ~CS8;
        options.c_cflag |= CS7;
        break;
    case 8://8 bits
        options.c_cflag  &= ~CS5;
        options.c_cflag  &= ~CS6;
        options.c_cflag  &= ~CS7;
        options.c_cflag |= CS8;
        break;
    default://8 bits
        options.c_cflag  &= ~CS5;
        options.c_cflag  &= ~CS6;
        options.c_cflag  &= ~CS7;
        options.c_cflag |= CS8;
        break;
    }

    switch(parity){
    case NOPARITY:
        options.c_cflag &= ~PARENB; //deshabilitar el bit de paridad
        options.c_iflag &= ~INPCK;  // disable input parity check
        break;
    case EVENPARITY:
        options.c_cflag &= ~PARODD; //paridad par
        options.c_cflag |= PARENB; //habilitar el bit de paridad
        options.c_iflag |= INPCK;  // enable input parity check
        break;
    case ODDPARITY:
        options.c_cflag |= PARODD; //paridad impar
        options.c_cflag |= PARENB; //habilitar el bit de paridad
        options.c_iflag |= INPCK;  // enable input parity check
        break;
    default:
        closeCommunication();
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": valor no valido de bits de paridad");
        return false;
        break;
    }

    switch(stop_bits){

    case STOPBIT:
        options.c_cflag &= ~CSTOPB;//Un bit de parada
        break;
    case TWO_STOPBIT:
        options.c_cflag |= CSTOPB;//Dos bits de parada
        break;
    default:
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": valor no valido de bits de parada");
        return false;
        break;
    }

    //configurar control de flujo
    switch (flow_control){
    case HARDWARE_FLOW:
        options.c_cflag |= CRTSCTS; //activar control de flujo por hardware
        options.c_iflag &= ~(IXON | IXOFF | IXANY); //desactivar control de flujo por software
        break;
    case SOFTWARE_FLOW:
        options.c_iflag |= (IXON | IXOFF | IXANY);//activar control de flujo por software
        options.c_cflag &= ~CRTSCTS; //desactivar control de flujo por hardware
        break;
    case NO_FLOW:
        options.c_cflag &= ~CRTSCTS; //desactivar control de flujo por hardware
        options.c_iflag &= ~(IXON | IXOFF | IXANY); //desactivar control de flujo por software
        break;
    default: //error, opcion no valida
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": valor no valido de control de flujo");
        return false;

    }


    //configurar tipo de entrada
    switch (type_input){
    case CANONICAL_INPUT:

        options.c_lflag |= (ICANON | ECHO | ECHOE);

        if (custom_input == CUSTOM_CANONICA) {
            //These special characters are active only in canonical input mode.
            //Los datos son enviados hasta que se introduce un <Line feed> ("\n") o <end of transmission> (EOF)
            options.c_cc[VEOF] = 111;//Por ejemlo, si indicas 111 el terminador sera la letra "o" en lugar de EOF
            //  options.c_cc[VEOL];
            //  options.c_cc[VEOL2];
            //  options.c_cc[VERASE];
            //  options.c_cc[VWERASE];
            //  options.c_cc[VKILL];
            //  options.c_cc[VREPRINT];
        }

        break;
    case RAW_INPUT:

        //Choosing Raw Input
        cfmakeraw(&options);
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        if (custom_input == CUSTOM_RAW){
            options.c_cc[VMIN]  = min_num; //Minimo numero de caracteres a leer (en caso de entrada raw)
            options.c_cc[VTIME] = time_out;//Tiempo para esperar a los datos (decimas de segundo)
        }
        break;
    default: //error, opcion no valida
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": tipo de entrada no valida");
        return false;

    }

    tcflush( fd, TCIOFLUSH);

    if ( tcsetattr (fd, TCSANOW, &options ) != 0) {
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": Error from tcsetattr");
        return false;

    }

    status = CI_CONNECTED;

    return true;

}

void CCCommunicationSerial::closeCommunication()
{
    if (status == CI_CONNECTED)  {
        status = CI_DISCONNECTED;
        if (fd >= 0)
            close(fd);
    }

}

void CCCommunicationSerial::reconnect()
{
    closeCommunication();
    openCommunication();
}

int CCCommunicationSerial::write(unsigned char *_buffer, int size)
{

    if (status != CI_CONNECTED) {
        report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected serial");
        return -1;
    }

    //tcflush(fd, TCOFLUSH);
    int n = ::write(fd, _buffer, size);

    if (n < 0)
        closeCommunication();

    return n;

}

int CCCommunicationSerial::read(unsigned char *_buffer, int size)
{

    if (status != CI_CONNECTED) {
        report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected serial");
        return -1;
    }

    //tcflush(fd, TCIFLUSH);
    int n = ::read(fd, _buffer, size);

    if (n < 0) //Puede ser igual que cero en modo RAW
        closeCommunication();

    return n;

}


