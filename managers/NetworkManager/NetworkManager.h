#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_H

#include "../../TypeDef.h"

#include "StateMachines/StateMachines.h"

struct ServerHandlerData
{
    
};

struct ServerData
{
    struct sockaddr_in cli_addr, serv_addr;
};

struct ClientData
{
    
    int connectionState;
    struct sockaddr_in cli_addr, serv_addr;

    ClientData()
    {
        connectionState = CLIENT_UNITIALIZED;
    }

    ClientData(char *clientData)
    {
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_port = htons(SERV_TCP_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    }
};

unsigned int init_NetworkManager(std::string message);

char *messageCRC(char *message);
int connectToServer(char *serverAdress, char *serverPort, int &sockfd);
int getActiveSearches(int sockfd) ;
int getActiveSearches(int sockfd);
int getChallange(int sockfd, char *challangeContainer, char *progressHash);
int postProgress(int sockfd, char *progress, char *challangeSolution);

#endif // SECP251K1_SANDBOX_NETWORKMANAGER_H