#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_H
#include "../managers.h"
#include "StateMachines/StateMachines.h"
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

struct Challange
{
    char key[CHALLANGE_NUMBER][LSB_STRING_SIZE];
    bool updatedFlag = false;
};

struct Solution
{
    char solution[CHALLANGE_NUMBER][SOLUTION_STRING_SIZE];
    bool solutionReady = true;
};

struct ProgressPackage
{
    char *serializedProgressData;
    char *dataSize;
    char progressDataHash[32];
};



struct ClientHandlerData
{
    char *clientAdressString;
    int &clientPort;
    bool &hostNotification;
    int &hostCommand;
    bool &SMnotification;
    Challange &challangeBundle;
    Solution &solutionBundle;
    ProgressPackage &progressData;
    sockaddr_in serv_addr;
};

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

char *messageCRC(char *message);
int connectToServer(char *serverAdress, char *serverPort, int &sockfd);
int getActiveSearches(int sockfd) ;
int getActiveSearches(int sockfd);
int getChallange(int sockfd, char *challangeContainer, char *progressHash);
int postProgress(int sockfd, char *progress, char *challangeSolution);

#endif // SECP251K1_SANDBOX_NETWORKMANAGER_H