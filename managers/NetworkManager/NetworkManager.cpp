#include "NetworkManager.h"
#include "../Ports.h"

#define MAX_SM_NUMBER 32u
#define NETWORK_SM_BUFFER 5u
unsigned int StateMachines = 0u;

unsigned int init_NetworkManager(NetworkManagerData networkManagerStruct)
{
    initPort(&networkManagerStruct.networkManagerRxPort, NETWORK_SM_BUFFER);
    // std::cout << "Network Manager initialized successfully\n" << std::endl;
    return NETWORK_MANAGER_E_OK;
}

/**
 * @brief Main network manager loop function that checks for changes in network messaging
 * 
 * @return unsigned int 
 */

unsigned int main_NetworkManager()
{
    ////ServerMode:
    //check frontend
        //if new valid request was received, create a new client handler
    //check clientHandlers
        ////OBS: client handlers should have direct access to the known points set, to reduce the need for the main function involvement
        //if clientHandlers need manager involvement, handle case
    //check satelliteHandlers
    return NETWORK_MANAGER_E_OK;
}

// struct sockaddr_in cli_addr, serv_addr;
// struct hostent *he;

/* Utility Functions */
// int sendMessage_TCP(char *message, unsigned int messageSize, int newsockfd)
// {
    
//     return -1;
// }

// int reciveMessage_TCP(char *messageBuffer)
// {
//     // set message receive timeout
//     // wait for message
//     // if received message
//      // send acknowledgement
//      // return OK
//     // else if timer ran out
//      // return TIMEOUT
//     return -1;
// }

// /* Server initial connection handler */

// int init_requestListener()
// {
//     //setup thread SM internal variables
//     return -1;
// }

// int checkRequestBuffer();

// int handle_ConnectionRequest()
// {
//     /// Check the integrity of the incomming request, and create the necessary data for the client connection
//     return -1;
// }

// int connect_Client()
// {
//     /// Create a new state machine containing the client connection parameters
//     // pthread_create(&thread_id, attr_flags, myThreadFun(), *arg);
//     return -1;
// }


// /* Server state machine functionality */

// int send_ActiveTargetsList(int sockfd, char *searchList)
// {
//     /// Memory Manager -> send string containing active search data
//     send(sockfd, searchList, strlen(searchList), 0);
//     return 0;
// }

// int send_Challange()
// {
//     ///TODO: implement sent challange functionality
//     return -1;
// }

// int handle_RegisterProgressUpdate_request()
// {
//     return -1;
// }

// int request_ProgressUpdate()
// {
//     return -1;
// }


// /* Client connection functionality */

// int request_ServerConnection()
// {
//     ///Send server request connection
//     return -1;
// }

// int connect_ToServer(char *serverAdress, char *serverPort, int &sockfd, struct sockaddr_in serv_addr)
// {
//     /// TODO: break part of the code into checking function
//     int hostPort;
//     if ((he = gethostbyname(serverAdress)) != NULL)
//     {
//         printf("Provided server adress: %s\n", inet_ntoa(serv_addr.sin_addr));
//     }
//     else
//     {
//         perror("Provided server adress invalid\n");
//         return CONN_MGR_E_INVALIDADRESS;
//     }

//     if (hostPort = strtoull(serverPort, NULL, 10))
//     {
//         printf("Server port: %d\n", hostPort);
//     }
//     else
//     {
//         perror("Invalid server port provided\n");
//         return CONN_MGR_E_INVALIDPORT;
//     }

//     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         perror("EROARE server: nu pot sa deschid stream socket");
//         return CONN_MGR_E_SOCKETFAULT;
//     }

//     bzero((char *)&serv_addr, sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     serv_addr.sin_port = htons(hostPort);

//     if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
//     {
//         perror("EROARE server: nu pot sa deschid stream socket");
//         return CONN_MGR_E_CONNECTFAULT;
//     }

//     return CONN_MGR_E_OK;
// }

// int request_ActiveTargets(int sockfd)
// {
//     char line[MESSAGE_SIZE_MAX];
//     int recivedMessageSize = -1;

//     send(sockfd, API_S_GET_ACTIVESEARCHES, strlen(API_S_GET_ACTIVESEARCHES), 0);
//     recivedMessageSize = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
//     line[recivedMessageSize] = '\0';
//     /// rebuild target files from host data -> Memory Manager
//     return 0;
// }

// int request_TargetData()
// {
//     return -1;
// }

// int request_RegisterProgressUpdate()
// {
//     return -1;
// }

// ///handle challange request GRAMMAR ERROR
// int receive_Challange(int sockfd, char *challangeContainer, char *progressMessage_Hash)
// {
//     char line[MESSAGE_SIZE_MAX];
//     send(sockfd, API_S_POST_REGISTERPROGRESS, strlen(API_S_POST_REGISTERPROGRESS), 0);
//     int response_size = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
//     if (strcmp(line, API_R_PROGRESS_HASH_REQUESTED) != 0)
//     {
//         return CONN_MGR_E_UNKNOWN_SERVER_RESPONSE;
//     }
//     else
//     {
//         // send(sockfd, progressHash, strlen(progressHash), 0);
//     }

//     response_size = recv(sockfd, challangeContainer, MESSAGE_SIZE_MAX, 0);
//     if (response_size < 1)
//     {
//         return CONN_MGR_E_SERVER_NOTRESPONDING;
//     }
//     else if (response_size > CHALLANGE_SIZE_MAX)
//     {
//         return CONN_MGR_E_MALFORMED_SERVER_RESPONSE;
//     }

//     return response_size;
// }

// ///send the progress data to the server
// int send_Progress(int sockfd, char *progress, int progressMessageSize, char *challangeSolution)
// {
//     char line[MESSAGE_SIZE_MAX];
//     send(sockfd, API_S_POST_REGISTERPROGRESS_SOLVED, strlen(API_S_POST_REGISTERPROGRESS_SOLVED), 0);
//     int response_size = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
//     if (strcmp(line, API_R_CONFIRM) == 0)
//     {
//         send(sockfd, progress, strlen(progress), 0);
//         response_size = recv(sockfd, &line, MESSAGE_SIZE_MAX, 0);
//         if (strcmp(line, API_R_CONFIRM) == 0)
//         {
//             return CONN_MGR_E_OK;
//         }
//         else
//         {
//             return CONN_MGR_E_UNKNOWN_SERVER_RESPONSE;
//         }
//     }
//     else if (strcmp(line, API_R_INVALID_SOLUTION) == 0)
//     {
//         return CONN_MGR_E_INVALID_CHALLANGE_SOLUTION;
//     }
//     else
//     {
//         return CONN_MGR_E_UNKNOWN_SERVER_RESPONSE;
//     }
//     return 0;
// }

