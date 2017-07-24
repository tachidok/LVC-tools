#ifndef CCCOMMUNICATIONCLIENT_H
#define CCCOMMUNICATIONCLIENT_H

#include "CACommunicationEthernet.h"
#include "Common/CCConfigFile.h"
#include "Report/CCReport.h"
#include "Report/CCMonitor.h"

using namespace std;

class CCCommunicationClient : public CACommunicationEthernet
{

public:
    CCCommunicationClient(const string &_configFile, const string &classname);
    ~CCCommunicationClient();

    void initialization(const string &_configFile, const string &classname);//Configurar el servidor o el cliente
    bool openCommunication(); //Abrir la conexion
    void closeCommunication(); //cerrar la conexion
    void reconnect(); //Cerrar y volver a abrir la conexion
    int write(unsigned char *_buffer, int size); //Enviar datos
    int write_bin(void *_buffer, int size); //Enviar datos
    int read(unsigned char *_buffer, int size); //Recibir datos

protected:

    string host_name;

};

#endif // CCCOMMUNICATIONCLIENT_H
