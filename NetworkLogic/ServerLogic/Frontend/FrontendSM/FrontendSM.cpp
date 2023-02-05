#include "FrontendSM.h"

#include <stdio.h>

unsigned int FrontendSM_init()
{
    printf("FrontendSM initialized\n");

    return 0u;
}

char *generateHandlerToken(char *token)
{
    //generate a unique token used for authentificating the client to the handler
    return token;
}

// unsigned int init_ServerFrontendSM(ServerFrontendSMStruct *messageStruct)
// {
//     gethostname(messageStruct->serverHostName, MAX_HOST_NAME_LENGTH); /* get local system host name */
//     DEBUG_MSG("\n---TCPServer started for host: %s\n", messageStruct->serverHostName);
    
//     messageStruct->he = gethostbyname(messageStruct->serverHostName); /* set host struct name by using the previously set variable */
//     DEBUG_MSG("\t(TCPServer INET ADRESS (IP) is %s )\n", inet_ntoa(messageStruct->serv_addr.sin_addr));
    
//     if ((messageStruct->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) /* bind a socket id to the server adress */
//     {
//         DEBUG_MSG("Server Frontend error: could not open socket\n");
//         return SERVER_FRONTEND_SM_E_SOCKETFAULT;
//     }

//     /* Initialize the port structure 'serv_addr' */
//     bzero((char *)&(messageStruct->serv_addr), sizeof(messageStruct->serv_addr)); //set all bits of serv_addr to 0
//     messageStruct->serv_addr.sin_family = AF_INET; /* set address structure to TCP/UDP */
//     messageStruct->serv_addr.sin_port = htons(messageStruct->server_tcp_port); /* translate port adress to network byte order and save to sin_port */
//     messageStruct->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* tell the server to listen on all available interfaces */

//     if (bind(messageStruct->sockfd, (struct sockaddr *)&(messageStruct->serv_addr), sizeof(messageStruct->serv_addr)) < 0) /* bind the socket to the port */
//     {
//         DEBUG_MSG("Server Frontend error: could not assign the socket to the physical adress");
//         messageStruct->error = SERVER_FRONTEND_SM_E_ADRESSFAULT;
//         messageStruct->SMstate = FAULT;
//         return 1;
//     }
//     messageStruct->bindedSM = true; /* set the struct binding status flag to true */
//     messageStruct->SMstate = INITIALIZED;
//     return 0;
// }

// unsigned int ServerFrontendSM(ServerFrontendSMStruct *messageStruct)
// {
//     while(messageStruct->SMstate != SHUTDOWN_REQUESTED)
//         switch(messageStruct->SMstate)
//         {
//             case UNINITIALIZED: /* SM data not initialized */
                
//                 break;

//             case INITIALIZED:
//                 if(messageStruct->inputMessage == NO_INPUT)
//                 {
//                     sleep(0.5); //if thread is initialized and no command has been issued, sleep before checking for a command
//                 }
//                 else if(messageStruct->inputMessage == START)
//                 {
//                     //start state machine
//                     messageStruct->SMstate = LISTENING; //set state machine status
//                     messageStruct->inputMessage = NO_INPUT; //reset the SM command buffer
//                 }
//                 else if(messageStruct->inputMessage == PRINT_DATA)
//                 {
//                     //print state machine data
//                     messageStruct->inputMessage = NO_INPUT;
//                 }
//                 else if(messageStruct->inputMessage == SHUTDOWN)
//                 {
//                     //shutdown state machine
//                     messageStruct->SMstate = SHUTDOWN_REQUESTED; //set state machine status
//                     messageStruct->inputMessage = NO_INPUT; //reset the SM command buffer
//                 }
//                 break;

//             case LISTENING:
//                 DEBUG_MSG("Server Frontend %s: awaiting connection on port: %d\n", messageStruct->ServerName, ntohs(messageStruct->serv_addr.sin_port));
//                 listen(messageStruct->sockfd, 5);
//                 while ((messageStruct->inputMessage != SHUTDOWN) && (messageStruct->inputMessage != STOP))
//                 {///TODO: create state switching function to simplify the state transitions
//                     bzero((char *)&(messageStruct->cli_addr), sizeof(messageStruct->cli_addr));
//                     messageStruct->clilen = sizeof(messageStruct->cli_addr);

//                     messageStruct->newsockfd = accept(messageStruct->sockfd, (struct sockaddr *)&(messageStruct->cli_addr), &(messageStruct->clilen));
//                     if (messageStruct->newsockfd < 0)
//                     {
//                         DEBUG_MSG("Server error: could not accept incomming connection");
//                         messageStruct->error = SERVER_FRONTEND_SM_E_CONNECTION_FAILED;
//                         messageStruct->SMstate = FAULT;
//                         break;
//                     }
//                     generateHandlerToken(messageStruct->line); //generate an authorization token to be used by the client
//                     send(messageStruct->newsockfd, (void *)(messageStruct->line), strlen(messageStruct->line), 0); //send the authorization token to the client

//                     //notify network manager that a new socket is present
//                     messageStruct->outputMessage = SOCKET_AVAILABLE;
//                 }
//                 messageStruct->SMstate = INITIALIZED;
//                 break;
            
//             case FAULT:
//                 if(messageStruct->inputMessage == NO_INPUT)
//                 {
//                     sleep(0.5); //if thread is initialized and no command has been issued, sleep before checking for a command
//                 }
//                 else if(messageStruct->inputMessage == RESTART)
//                 {
//                     //start state machine
//                     messageStruct->SMstate = UNINITIALIZED; //set state machine status
//                     messageStruct->inputMessage = NO_INPUT; //reset the SM command buffer
//                 }
//                 else if(messageStruct->inputMessage == PRINT_DATA)
//                 {
//                     //print state machine data
//                     messageStruct->inputMessage = NO_INPUT;
//                 }
//                 else if(messageStruct->inputMessage == SHUTDOWN)
//                 {
//                     //shutdown state machine
//                     messageStruct->SMstate = SHUTDOWN_REQUESTED; //set state machine status
//                     messageStruct->inputMessage = NO_INPUT; //reset the SM command buffer
//                 }
//                 break;
//             default:
//                 //unknown machine state

//                 break;
//         }
//     return 0;
// }