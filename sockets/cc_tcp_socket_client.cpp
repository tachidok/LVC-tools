#include "CCCommunicationClient.h"

extern CCReport report;
extern CCMonitor monitor;

CCCommunicationClient::CCCommunicationClient(const string &_configFile, const string &classname)
{
    report.updateMessageRecord(string(__PRETTY_FUNCTION__));
    initialization(_configFile, classname);
}

CCCommunicationClient::~CCCommunicationClient()
{
    report.updateMessageRecord(string(__PRETTY_FUNCTION__));
    closeCommunication();
}

void CCCommunicationClient::initialization(const string &_configFile, const string &classname)
{
    port = 2001;
    host_name = "localhost";
    fd = -1;
    status = CI_DISCONNECTED;

    CCConfigFile cfg(_configFile);

    port = cfg.getValueOfInt(classname +".port");
    host_name = cfg.getValueOfString(classname +".host_name");

}

bool CCCommunicationClient::openCommunication()
{

    struct sockaddr_in serv_addr;
    struct hostent *server;

    //check that  is not already connected
    if (status == CI_CONNECTED){
        //report.warningMessage(string(__PRETTY_FUNCTION__) + ": already connected");
        return true;
    }

    // Open socket
    //used address the internet domain and stream sockets treat communications as a continuous stream of characters
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        status = CI_DISCONNECTED;
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": opening socket");
        return false;
    }

    //Get host name
    server = gethostbyname(host_name.c_str());

    if (server == NULL) {
        status = CI_DISCONNECTED;
        close(fd);
        report.errorMessage(string(__PRETTY_FUNCTION__) + ": Host not found");
        return false;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(port);

    //printf("Cliente: Solicitar conexion\n");

    if (connect(fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        status = CI_DISCONNECTED;
        close(fd);
        //report.errorMessage(string(__PRETTY_FUNCTION__) + ": The client could not connect");
        return false;
    }

    status = CI_CONNECTED;

    return true;

}

void CCCommunicationClient::closeCommunication()
{
    if (status == CI_CONNECTED)  {
        status = CI_DISCONNECTED;
        if (fd >= 0)
            close(fd);
    }
}

void CCCommunicationClient::reconnect()
{
    closeCommunication();
    openCommunication();
}

int CCCommunicationClient::write(unsigned char *_buffer, int size)
{

    if (status != CI_CONNECTED) {
        //report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected socket");
        return -1;
    }

    int n = ::write(fd, _buffer, size);

    if (n < 0)
        closeCommunication();

    return n;

}

int CCCommunicationClient::write_bin(void *_buffer, int size)
{
    if (status != CI_CONNECTED) {
        //report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected socket");
        return -1;
    }

    int n = ::write(fd, _buffer, size);

    if (n < 0)
        closeCommunication();

    return n;
}

int CCCommunicationClient::read(unsigned char *_buffer, int size)
{

    if (status != CI_CONNECTED) {
        //report.warningMessage(string(__PRETTY_FUNCTION__) + ":there is not connected socket");
        return -1;
    }

    int n = ::read(fd, _buffer, size);

    if (n < 0)
        closeCommunication();

    return n;

}
