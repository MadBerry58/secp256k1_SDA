#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_H
#include "../../src/headers/Iterators.h"
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int connectToServer(char *serverAdress, char *serverPort, int &sockfd);
int getActiveSearches(int sockfd) ;
int getActiveSearches(int sockfd);
int getChallange(int sockfd, char *challangeContainer, char *progressHash);
int postProgress(int sockfd, char *progress, char *challangeSolution);

#endif // SECP251K1_SANDBOX_NETWORKMANAGER_H