#include "ClientSM.h"

#include <stdio.h>

unsigned int init_ClientSM(ClientSM_struct *message)
{
    printf("ClientSM started\n");
    return 0;
}

unsigned int ClientSM(ClientSM_struct *message)
{
    //send starting acknowledgement
    //send started acknowledgement
    //send waiting for command acknowledgement
    return 0;
}

// unsigned int clientFrontendSM_TCP(char *serverAdressString, int serverPort, bool &hostNotification, int &hostCommand, bool &SMnotification,
//                      ClientSMConnection connectionSM_state, Challange &challangeBundle, Solution &solutionBundle,
//                      ProgressPackage progressData);
// {
//     connectionSM_state = CLIENT_SM_STATE_UNITIALIZED;
//     unsigned int responseSize = -1, expectedResponseSize = -1, progressDataSize = -1, 
//                     progressDataMessages = -1, disconnectionReason = -1, requestSize = -1, 
//                     serverSocket = -1, handlerSocket = -1, receivedMessageSize = -1, handlerPort = -1;
//     char handlerToken[HANDLERTOKENSIZE], messageBuffer[MAX_MESSAGE_LINE], 
//             request[MAX_MESSAGE_LINE], handlerPortString[10], response[MAX_MESSAGE_LINE];
//     socklen_t socketLength;
//     struct sockaddr_in serverAddress, handlerAdress;

//     SM_RESET:
//     for ( ;; )
//     {
//         switch (connectionSM_state)
//         {
//             case CLIENT_SM_STATE_INIT:
//                 if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) // initialize socket as datagram for UDP connection
//                 {
//                     DEBUG_MSG("Could not open datagram socket");
//                     return CLIENT_SM_E_SOCKETFAULT;
//                 }

//                 serverAddress.sin_family = AF_INET;
//                 serverAddress.sin_port = htons(serverPort);
//                 serverAddress.sin_addr.s_addr = inet_addr(serverAdressString);
//                 connectionSM_state = CLIENT_SM_STATE_REQUESTING_HANDLER;
//                 break;

//             case CLIENT_SM_STATE_REQUESTING_HANDLER:
//                 ////request a client handler SM
//                 strcpy(request, CLIENT_SM_REQUEST_HANDLER);
//                 requestSize = strlen(CLIENT_SM_REQUEST_HANDLER);
//                 sendto(serverSocket, request, requestSize, 0, (const struct sockaddr *)&serverAddress, sizeof(serverAddress));
//                 // set timer

//                 // wait for request confirmation
//                 responseSize = recvfrom(serverSocket, response, MAX_MESSAGE_LINE,
//                                     MSG_WAITALL, (struct sockaddr *)&serverAddress,
//                                     &socketLength);
//                 // messageBuffer[receivedMessageSize] = '\0';

//                 expectedResponseSize = strlen(SERVER_SM_RESPONSE_HANDLERID);

//                 if (requestSize > expectedResponseSize)
//                 {
//                     DEBUG_MSG("Response size not as expected");
//                     return CLIENT_SM_E_MALFORMED_SERVER_RESPONSE;
//                 }
//                 // read response type
//                 strncpy(messageBuffer, response, expectedResponseSize);

//                 if (strcmp(messageBuffer, SERVER_SM_RESPONSE_HANDLERID) != 0)
//                 {
//                     DEBUG_MSG("Invalid response to handler request");
//                     return CLIENT_SM_E_MALFORMED_SERVER_RESPONSE;
//                 }

//                 // Read provided port
//                 strncpy(handlerPortString, &response[expectedResponseSize], PORTLENGTH);

//                 // register handler port
//                 handlerPort = atoi(handlerPortString);

//                 // register handler token
//                 strncpy(handlerToken, &response[expectedResponseSize + PORTLENGTH], HANDLERTOKENSIZE);

//                 connectionSM_state = CLIENT_SM_STATE_CONNECTING_TO_HANDLER;
//                 break;

//             case CLIENT_SM_STATE_CONNECTING_TO_HANDLER:
//                 ////connect to the supplied client handler SM
//                 if ((handlerSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) // initialize socket as datagram for UDP connection
//                 {
//                     DEBUG_MSG("Could not open stream socket");
//                     return CLIENT_SM_E_SOCKETFAULT;
//                 }

//                 handlerAdress.sin_family = AF_INET;
//                 handlerAdress.sin_port = htons(handlerPort);
//                 handlerAdress.sin_addr.s_addr = inet_addr(serverAdressString);

//                 if (connect(handlerSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0)
//                 {
//                     DEBUG_MSG("Handler connection error")
//                     return CLIENT_SM_E_CONNECTFAULT;
//                 }

//                 // send the handler token
//                 send(handlerSocket, handlerToken, HANDLERTOKENSIZE, 0);
//                 responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                 if (strcmp(response, HANDLER_SM_RESPONSE_CONFIRMCONNECTION) != 0)
//                 {
//                     DEBUG_MSG("Handler refused connection");
//                     return CLIENT_SM_E_SOCKETFAULT;
//                 }

//                 connectionSM_state = CLIENT_SM_STATE_CONNECTED;

//             case CLIENT_SM_STATE_CONNECTED:
//                 ////check for notification flags (messages from main)
//                 for(;;)
//                 {
//                     if(hostNotification)
//                     {
//                         //send message from the host process
//                         //wait for handler response
//                         if (strcmp(request, CLIENT_SM_REQUEST_REGISTERPROGRESS) == 0)
//                         {
//                             //process the progress registration in a separate state
//                             connectionSM_state = CLIENT_SM_STATE_REQUESTING_PROGRESS_REGISTRATION;
//                         }
//                         else
//                         {
//                             //process a lightweight request internally
//                         }
//                     }
//                     else if((responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, MSG_DONTWAIT)) > 0)
//                     {
//                         //process the recived message
//                         if (strcmp(response, HANDLER_SM_REQUEST_REQUESTPROGRESS))
//                         {
//                         //process the progress registration in a separate state
//                         connectionSM_state = CLIENT_SM_STATE_REQUESTING_PROGRESS_REGISTRATION;
//                         }
//                     }
//                 }
//                 break;

//             case CLIENT_SM_STATE_REQUESTING_PROGRESS_REGISTRATION:
//                 strcpy(request, CLIENT_SM_REQUEST_REGISTERCHALLANGE);
//                 strcat(request, progressData.progressDataHash);
//                 requestSize = strlen(CLIENT_SM_REQUEST_REGISTERCHALLANGE);
//                 send(handlerSocket, request, requestSize, 0);
//                 responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                 expectedResponseSize = strlen(HANDLER_SM_RESPONSE_CHALLANGEKEYS) + CHALLANGE_SIZE_MAX;
//                 if (responseSize < expectedResponseSize)
//                 {
//                     DEBUG_MSG("Handler challange issuing failed");
//                     return CLIENT_SM_E_MALFORMED_HANDLER_RESPONSE;
//                 }
//                 for (int i = 0; i < CHALLANGE_NUMBER; i++)
//                 {
//                     strncpy(challangeBundle.key[i], &response[i * LSB_STRING_SIZE], LSB_STRING_SIZE);
//                 }
//                 SMnotification = true; //notify the host the challange has been updated

//                 while (hostNotification == false)
//                 {
//                     //wait for the host to calculate the challange solution
//                 }

//                 strcpy(request, CLIENT_SM_REQUEST_REGISTERPROGRESS);
//                 for(int i = 0; i < CHALLANGE_NUMBER; i++)
//                 {
//                     strcat(request, solutionBundle.solution[i]);
//                 }
//                 send(handlerSocket, request, requestSize, 0);

//                 expectedResponseSize = strlen(HANDLER_SM_RESPONSE_CHALLANGEOK);
//                 responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                 if (responseSize < expectedResponseSize)
//                 {
//                     DEBUG_MSG("Handler did not confirm the challange solution");
//                     return CLIENT_SM_E_INVALID_CHALLANGE_SOLUTION;
//                 }
//                 connectionSM_state = CLIENT_SM_STATE_SENDING_PROGRESS;
//                 break;

//             case CLIENT_SM_STATE_SENDING_PROGRESS:
//                 // send progress data
//                 unsigned int messageIndex = 0;
//                 strcpy(request, CLIENT_SM_REQUEST_PROGRESSDATASPACE);
//                 strcat(request, progressData.dataSize); ///TODO: change 10u to a constant ID
//                 progressDataSize = atoi(progressData.dataSize);
//                 progressDataMessages = progressDataSize / MAX_MESSAGE_LINE;
//                 for (int i = 0; i < progressDataMessages; i++)
//                 {
//                     messageIndex = i * MAX_MESSAGE_LINE;
//                     strncpy(request, &progressData.serializedProgressData[messageIndex], PROGRESSDATA_DATACONTAINERSIZE);

//                     strcat(request, "I");
//                     strcat(request, std::to_string(i).c_str());

//                     strcpy(messageBuffer, messageCRC(request));

//                     strcat(request, "C");
//                     strcat(request, messageBuffer);

//                     send(handlerSocket, request, requestSize, 0);

//                     strcpy(messageBuffer, "R");
//                     strcat(messageBuffer, messageCRC(request));
//                     responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                     for (int j = 0; j < SM_RETRY_COUNT; j++)
//                     {
//                         if(strcmp(response, messageBuffer) != 0)
//                         {
//                             DEBUG_MSG("Ciclic Redundancy Check failed");
//                             send(handlerSocket, request, requestSize, 0);
//                             responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                         }
//                         else
//                         {
//                             break;
//                         }
//                     }

                    
//                 }

//             case CLIENT_SM_STATE_DISCONNECTED:

//                 while (CLIENT_SM_STATE_SHUTDOWN != connectionSM_state)
//                 {
//                     if (hostNotification)
//                     {
//                         if (HOST_SM_OK == hostCommand)
//                         {
//                             exit(0);
//                         }
//                         else if (HOST_SM_RESTART_REINIT == hostCommand)
//                         {
//                             connectionSM_state = CLIENT_SM_STATE_INIT;
//                         }
//                         else if (HOST_SM_RESTART_NOINIT == hostCommand)
//                         {
//                             connectionSM_state = CLIENT_SM_STATE_REQUESTING_HANDLER;
//                         }
//                 }
//                 break;

//             case CLIENT_SM_STATE_SHUTDOWN:
//                 break;

//             default:

//                 break;
//             }
//         }
//     }
// }