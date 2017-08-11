#include "CCCommunicationUDPClient.h"

extern CCReport report;
extern CCMonitor monitor;

// ========================================================================
// Constructor
// ========================================================================
CCCommunicationUDPClient::CCCommunicationUDPClient(const string &configuration_file,
                                                   const string &type_name)
{
    report.updateMessageRecord(string(__PRETTY_FUNCTION__));
    initialization(configuration_file, type_name);
}

// ========================================================================
// Destructor
// ========================================================================
CCCommunicationUDPClient::~CCCommunicationUDPClient()
{
    report.updateMessageRecord(string(__PRETTY_FUNCTION__));
    closeCommunication();
}
// ========================================================================
// Read data from configuration file (then why is it called initialization?)
// ========================================================================
void CCCommunicationUDPClient::initialization(const string &configuration_file,
                                              const string &type_name)
{
    // Assign default values
    port = 2001;
    Input_port = 4000;
    host_name = "localhost";
    fd = -1;
    read_fd = -1;
    status = CI_DISCONNECTED;

    // Get the socket configuration (destination address and port) from the
    // input configuration file
    CCConfigFile cfg(configuration_file);

    host_name = cfg.getValueOfString(type_name +".host_name");
    port = cfg.getValueOfInt(type_name +".port");
    Input_port = cfg.getValueOfInt(type_name +".input_port");


}

// ========================================================================
// Opens an UDP connection type
// ========================================================================
bool CCCommunicationUDPClient::openCommunication()
{
    // Before anything else check whether the socket is already connected or not
    if (status == CI_CONNECTED){
        status = CI_DISCONNECTED;
        //report.warningMessage(string(__PRETTY_FUNCTION__) + ": already connected");
        return true;
    }

    // --------------------------------------------
    // Create write communication
    // --------------------------------------------
    // Open socket (open an UDP connection)
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (fd < 0) {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening UDP socket");
        return false;
    }

    // Initialise data structure
    // Set to zero
    memset((char *) &Socket_address_out, 0, sizeof(Socket_address_out));
    // Set family type
    Socket_address_out.sin_family = AF_INET;
    // Set the port
    Socket_address_out.sin_port = htons(port);

    // Get the length of the data structure
    Socket_length_out = sizeof(Socket_address_out);

    // Initialise communication?
    if (inet_aton(host_name.c_str() , &Socket_address_out.sin_addr) == 0)
    {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening UDP socket [inet_aton() failed]");
        return false;
    }

    // Set the timeout for writing operations
    struct timeval timeout;
    timeout.tv_sec = 0; // 0 second
    timeout.tv_usec = 100000; // 0 micro-seconds
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening UDP socket [Write communication - setsockopt() timeout failed]");
        return false;
    }

    // --------------------------------------------
    // Create read communication
    // --------------------------------------------
    if ((read_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening UDP server socket [Write communication - inet_aton() failed]");
        return false;
    }

    memset((char *) &Socket_address_in, 0, sizeof(Socket_address_in));
    Socket_address_in.sin_family = AF_INET;
    Socket_address_in.sin_port = htons(Input_port);
    Socket_address_in.sin_addr.s_addr = htonl(INADDR_ANY);

    // Indicate the reading port
    if (bind( read_fd ,(struct sockaddr *)  &Socket_address_in, sizeof(Socket_address_in))==-1)
    {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening UDP server bind [Read communication - inet_aton() failed]");
        return false;
    }

    // Set the timeout for reading operations
    timeout.tv_sec = 0; // 1 second
    timeout.tv_usec = 100000; // 0 micro-seconds
    if (setsockopt(read_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening UDP socket [Read communication - setsockopt() timeout failed]");
        return false;
    }

    // Success
    status = CI_CONNECTED;

    return true;

}

// ========================================================================
// Close communication
// ========================================================================
void CCCommunicationUDPClient::closeCommunication()
{
    if (status == CI_CONNECTED)  {
        status = CI_DISCONNECTED;
        if (fd >= 0)
            close(fd);
        if (read_fd >= 0)
            close(read_fd);
    }
}

// ========================================================================
// Try re-connection by closing and opening a connection
// ========================================================================
void CCCommunicationUDPClient::reconnect()
{
    closeCommunication();
    openCommunication();
}

int CCCommunicationUDPClient::write(unsigned char *buffer, int size)
{
    // Check connection status
    if (status != CI_CONNECTED) {
        report.warningMessage(string(__PRETTY_FUNCTION__) + ": The UDP socket is disconnected");
        return -1;
    }

    // Send data
    return sendto(fd, buffer, size, 0 , (struct sockaddr *) &Socket_address_out, Socket_length_out);

}

int CCCommunicationUDPClient::read(unsigned char *buffer, int size)
{
    // Check connection status
    if (status != CI_CONNECTED) {
        report.warningMessage(string(__PRETTY_FUNCTION__) + ": The UDP socket is disconnected");
        return -1;
    }

    // Get the length of the data structure
    Socket_length_in = sizeof(Socket_address_in);
    // Clean the output buffer
    bzero(buffer, sizeof(buffer));
    // Read data
    return recvfrom(read_fd, buffer, size, 0 , (struct sockaddr *) &Socket_address_in, &Socket_length_in);

}
