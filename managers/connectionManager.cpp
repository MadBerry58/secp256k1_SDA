#include "headers/connectionManager.h"

struct sockaddr_in cli_addr, serv_addr;
struct hostent *he;

int connectToServer(char *serverAdress, char *serverPort, int &sockfd, struct sockaddr_in serv_addr)
{
    ///TODO: break part of the code into checking function
    int hostPort;
    if ((he = gethostbyname(serverAdress)) != NULL)
    {
        printf("Provided server adress: %s\n", inet_ntoa(serv_addr.sin_addr));
    }
    else
    {
        perror("Provided server adress invalid\n");
        return CONN_MGR_E_INVALIDADRESS;
    }

    if (hostPort = strtoull(serverPort, NULL, 10))
    {
        printf("Server port: %d\n", hostPort);
    }
    else
    {
        perror("Invalid server port provided\n");
        return CONN_MGR_E_INVALIDPORT;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("EROARE server: nu pot sa deschid stream socket");
        return CONN_MGR_E_SOCKETFAULT;
    }
    
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(hostPort);

    if ( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
    {
        perror("EROARE server: nu pot sa deschid stream socket");
        return CONN_MGR_E_CONNECTFAULT;
    }

    return CONN_MGR_E_OK;
}

int connectClient();


int chooseTarget();

int registerClientTarget();


int getActiveSearches(int sockfd)
{
    char line[MESSAGE_SIZE_MAX];
    int recivedMessageSize = -1;
    
    send(sockfd, API_S_GET_ACTIVESEARCHES, strlen(API_S_GET_ACTIVESEARCHES), 0);
    recivedMessageSize = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
    line[recivedMessageSize] = '\0';
    ///rebuild target files from host data -> Memory Manager
    return 0;
}

int giveActiveSearches(int sockfd, char *searchList)
{
    /// Memory Manager -> send string containing active search data
    send(sockfd, searchList, strlen(searchList), 0);
    return 0;
}


int getChallange(int sockfd, char *challangeContainer, char *progressHash)
{
    char line[MESSAGE_SIZE_MAX];
    send(sockfd, API_S_POST_REGISTERPROGRESS, strlen(API_S_POST_REGISTERPROGRESS), 0);
    int response_size = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
    if (strcmp(line, API_R_PROGRESS_HASH_REQUESTED) != 0)
    {
        return CONN_MGR_E_UNKNOWN_SERVER_RESPONSE;
    }
    else
    {
        send(sockfd, progressHash, strlen(progressHash), 0);
    }

    response_size = recv(sockfd, challangeContainer, MESSAGE_SIZE_MAX, 0);
    if (response_size < 1)
    {
        return CONN_MGR_E_SERVER_NOTRESPONDING;
    }
    else 
    if (response_size > CHALLANGE_SIZE_MAX)
    {
        return CONN_MGR_E_MALFORMED_SERVER_RESPONSE;
    }

    return response_size;
}

int giveChallange();


int postProgress(int sockfd, char *progress, char *challangeSolution)
{
    char line[MESSAGE_SIZE_MAX];
    send(sockfd, API_S_POST_REGISTERPROGRESS_SOLVED, strlen(API_S_POST_REGISTERPROGRESS_SOLVED), 0);
    int response_size = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
    if (strcmp(line, API_R_CONFIRM) == 0)
    {
        send(sockfd, progress, strlen(progress), 0);
        response_size = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
        if (strcmp(line, API_R_CONFIRM) == 0)
        {
            return CONN_MGR_E_OK;
        }
        else
        {
            return CONN_MGR_E_UNKNOWN_SERVER_RESPONSE;
        }
        
    }
    else 
    if (strcmp(line, API_R_INVALID_SOLUTION) == 0)
    {
        return CONN_MGR_E_INVALID_CHALLANGE_SOLUTION;
    }
    else
    {
        return CONN_MGR_E_UNKNOWN_SERVER_RESPONSE;
    }
    return 0;
}

int getProgress();


