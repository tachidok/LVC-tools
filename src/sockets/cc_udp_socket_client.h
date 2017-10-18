#ifndef CCCOMMUNICATIONUDPCLIENT_H
#define CCCOMMUNICATIONUDPCLIENT_H

#include "CACommunicationEthernet.h"
#include "Common/CCConfigFile.h"
#include "Report/CCReport.h"
#include "Report/CCMonitor.h"

#include<arpa/inet.h>
#include<sys/socket.h>

// A class that implement a UDP client type (non-blocking)
class CCCommunicationUDPClient : public CACommunicationEthernet
{
public:

    // Constructor
    CCCommunicationUDPClient(const string &configuration_file, const string &type_name);

    // Destructor
    ~CCCommunicationUDPClient();

    // Read data from configuration file (then why is it called initialization?)
    void initialization(const string &configuration_file, const string &type_name);

    // Opens an UDP connection type
    bool openCommunication();

    // Close communication
    void closeCommunication();

    // Try re-connection by closing and opening a connection
    void reconnect();

    // Send data
    int write(unsigned char *buffer, int size);

    // Read data
    int read(unsigned char *buffer, int size); //Recibir datos

protected:

    string host_name;
    int Input_port;

    int read_fd;

    // Required for write operation
    struct sockaddr_in Socket_address_out;
    socklen_t Socket_length_out;

    // Required for read operation
    struct sockaddr_in Socket_address_in;
    socklen_t Socket_length_in;

};

#endif // CCCOMMUNICATIONUDPCLIENT_H
