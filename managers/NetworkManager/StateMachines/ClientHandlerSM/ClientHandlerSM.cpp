#include "ClientHandlerSM.h"

void init_ClientHandlerSM(clientHandlerSMStruct *messageStruct)
{
    
}

// int clientHandlerSM(struct ClientHandlerData initializingData)
// {
//     initializingData.connectionSM_state = CLIENT_HANDLER_SM_UNINITIALIZED;
//     unsigned int responseSize = -1, expectedResponseSize = -1, progressDataSize = -1,
//                  progressDataMessages = -1, disconnectionReason = -1, requestSize = -1,
//                  clientSocket = -1, handlerSocket = -1, receivedMessageSize = -1, handlerPort = -1;
//     char handlerToken[HANDLERTOKENSIZE], messageBuffer[MAX_MESSAGE_LINE],
//         request[MAX_MESSAGE_LINE], handlerPortString[10], response[MAX_MESSAGE_LINE];
//     socklen_t socketLength;
//     struct sockaddr_in clientAddress, handlerAdress;

//     initializingData.connectionSM_state = CLIENT_HANDLER_SM_INIT;

//     SM_RESET:

//     for (;;)
//     {
//         switch (initializingData.connectionSM_state)
//         {
//         case CLIENT_HANDLER_SM_INIT:
//             if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) // initialize socket as datagram for UDP connection
//             {
//                 DEBUG_MSG("Could not open stream socket");
//                 return CLIENT_HANDLER_SM_E_SOCKETFAULT;
//             }

//             clientAddress.sin_family = AF_INET;
//             clientAddress.sin_port = htons(initializingData.clientPort);
//             clientAddress.sin_addr.s_addr = inet_addr(initializingData.clientAdressString);
//             initializingData.connectionSM_state = CLIENT_HANDLER_SM_WAITINGCONNECTION;
//             break;

//         case CLIENT_HANDLER_SM_WAITINGCONNECTION:
//             ////request a client handler SM
//             strcpy(request, CLIENT_SM_REQUEST_HANDLER);
//             requestSize = strlen(CLIENT_SM_REQUEST_HANDLER);
//             sendto(clientSocket, request, requestSize, 0, (const struct sockaddr *)&clientAddress, sizeof(clientAddress));
//             // set timer

//             // wait for request confirmation
//             responseSize = recvfrom(clientSocket, response, MAX_MESSAGE_LINE,
//                                     MSG_WAITALL, (struct sockaddr *)&clientAddress,
//                                     &socketLength);
//             // messageBuffer[receivedMessageSize] = '\0';

//             expectedResponseSize = strlen(SERVER_SM_RESPONSE_HANDLERID);

//             if (requestSize > expectedResponseSize)
//             {
//                 DEBUG_MSG("Response size not as expected");
//                 return CLIENT_SM_E_MALFORMED_SERVER_RESPONSE;
//             }
//             // read response type
//             strncpy(messageBuffer, response, expectedResponseSize);

//             if (strcmp(messageBuffer, SERVER_SM_RESPONSE_HANDLERID) != 0)
//             {
//                 DEBUG_MSG("Invalid response to handler request");
//                 return CLIENT_SM_E_MALFORMED_SERVER_RESPONSE;
//             }

//             // Read provided port
//             strncpy(handlerPortString, &response[expectedResponseSize], PORTLENGTH);

//             // register handler port
//             handlerPort = atoi(handlerPortString);

//             // register handler token
//             strncpy(handlerToken, &response[expectedResponseSize + PORTLENGTH], HANDLERTOKENSIZE);

//             initializingData.connectionSM_state = CLIENT_HANDLER_SM_RECIVED_CONNECTIONREQUEST;
//             break;

//         case CLIENT_HANDLER_SM_RECIVED_CONNECTIONREQUEST:
//             ////connect to the supplied client handler SM
//             if ((handlerSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) // initialize socket as datagram for UDP connection
//             {
//                 DEBUG_MSG("Could not open stream socket");
//                 return CLIENT_SM_E_SOCKETFAULT;
//             }

//             handlerAdress.sin_family = AF_INET;
//             handlerAdress.sin_port = htons(handlerPort);
//             handlerAdress.sin_addr.s_addr = inet_addr(initializingData.clientAdressString);

//             if (connect(handlerSocket, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) != 0)
//             {
//                 DEBUG_MSG("Handler connection error")
//                 return CLIENT_SM_E_CONNECTFAULT;
//             }

//             // send the handler token
//             send(handlerSocket, handlerToken, HANDLERTOKENSIZE, 0);
//             responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//             if (strcmp(response, HANDLER_SM_RESPONSE_CONFIRMCONNECTION) != 0)
//             {
//                 DEBUG_MSG("Handler refused connection");
//                 return CLIENT_SM_E_SOCKETFAULT;
//             }

//             initializingData.connectionSM_state = CLIENT_HANDLER_SM_CONNECTED;

//         case CLIENT_HANDLER_SM_CONNECTED:
//             ////check for notification flags (messages from main)
//             for (;;)
//             {
//                 if (initializingData.hostNotification)
//                 {
//                     // send message from the host process
//                     // wait for handler response
//                     if (strcmp(request, CLIENT_SM_REQUEST_REGISTERPROGRESS) == 0)
//                     {
//                         // process the progress registration in a separate state
//                         initializingData.connectionSM_state = CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST;
//                     }
//                     else
//                     {
//                         // process a lightweight request internally
//                     }
//                 }
//                 else if ((responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, MSG_DONTWAIT)) > 0)
//                 {
//                     // process the recived message
//                     if (strcmp(response, HANDLER_SM_REQUEST_REQUESTPROGRESS))
//                     {
//                         // process the progress registration in a separate state
//                         initializingData.connectionSM_state = CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST;
//                     }
//                 }
//             }
//             break;

//         case CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST:
//             strcpy(request, CLIENT_SM_REQUEST_REGISTERCHALLANGE);
//             strcat(request, initializingData.progressData.progressDataHash);
//             requestSize = strlen(CLIENT_SM_REQUEST_REGISTERCHALLANGE);
//             send(handlerSocket, request, requestSize, 0);
//             responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//             expectedResponseSize = strlen(HANDLER_SM_RESPONSE_CHALLANGEKEYS) + CHALLANGE_SIZE_MAX;
//             if (responseSize < expectedResponseSize)
//             {
//                 DEBUG_MSG("Handler challange issuing failed");
//                 return CLIENT_SM_E_MALFORMED_HANDLER_RESPONSE;
//             }
//             for (int i = 0; i < CHALLANGE_NUMBER; i++)
//             {
//                 strncpy(initializingData.challangeBundle.key[i], &response[i * LSB_STRING_SIZE], LSB_STRING_SIZE);
//             }
//             initializingData.SMnotification = true; // notify the host the challange has been updated

//             while (initializingData.hostNotification == false)
//             {
//                 // wait for the host to calculate the challange solution
//             }

//             strcpy(request, CLIENT_SM_REQUEST_REGISTERPROGRESS);
//             for (int i = 0; i < CHALLANGE_NUMBER; i++)
//             {
//                 strcat(request, initializingData.solutionBundle.solution[i]);
//             }
//             send(handlerSocket, request, requestSize, 0);

//             expectedResponseSize = strlen(HANDLER_SM_RESPONSE_CHALLANGEOK);
//             responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//             if (responseSize < expectedResponseSize)
//             {
//                 DEBUG_MSG("Handler did not confirm the challange solution");
//                 return CLIENT_SM_E_INVALID_CHALLANGE_SOLUTION;
//             }
//             initializingData.connectionSM_state = CLIENT_HANDLER_SM_REGISTERING_PROGRESS;
//             break;

//         case CLIENT_HANDLER_SM_REGISTERING_PROGRESS:
//             // send progress data
//             unsigned int messageIndex = 0;
//             strcpy(request, CLIENT_SM_REQUEST_PROGRESSDATASPACE);
//             strcat(request, initializingData.progressData.dataSize); /// TODO: change 10u to a constant ID
//             progressDataSize = atoi(initializingData.progressData.dataSize);
//             progressDataMessages = progressDataSize / MAX_MESSAGE_LINE;
//             for (int i = 0; i < progressDataMessages; i++)
//             {
//                 messageIndex = i * MAX_MESSAGE_LINE;
//                 strncpy(request, &initializingData.progressData.serializedProgressData[messageIndex], PROGRESSDATA_DATACONTAINERSIZE);

//                 strcat(request, "I");
//                 strcat(request, std::to_string(i).c_str());

//                 strcpy(messageBuffer, messageCRC(request));

//                 strcat(request, "C");
//                 strcat(request, messageBuffer);

//                 send(handlerSocket, request, requestSize, 0);

//                 strcpy(messageBuffer, "R");
//                 strcat(messageBuffer, messageCRC(request));
//                 responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                 for (int j = 0; j < SM_RETRY_COUNT; j++)
//                 {
//                     if (strcmp(response, messageBuffer) != 0)
//                     {
//                         DEBUG_MSG("Ciclic Redundancy Check failed");
//                         send(handlerSocket, request, requestSize, 0);
//                         responseSize = recv(handlerSocket, response, MAX_MESSAGE_LINE, 0);
//                     }
//                     else
//                     {
//                         break;
//                     }
//                 }
//             }

//         case CLIENT_HANDLER_SM_DISCONNECTED:

//             while (CLIENT_SM_STATE_SHUTDOWN != initializingData.connectionSM_state)
//             {
//                 if (initializingData.hostNotification)
//                 {
//                     if (HOST_SM_OK == initializingData.hostCommand)
//                     {
//                         exit(0);
//                     }
//                     else if (HOST_SM_RESTART_REINIT == initializingData.hostCommand)
//                     {
//                         initializingData.connectionSM_state = CLIENT_HANDLER_SM_INIT;
//                     }
//                     else if (HOST_SM_RESTART_NOINIT == initializingData.hostCommand)
//                     {
//                         initializingData.connectionSM_state = CLIENT_HANDLER_SM_WAITINGCONNECTION;
//                     }
//                 }
//                 break;

//             case CLIENT_HANDLER_SM_SHUTDOWN:
//                 break;

//             default:

//                 break;
//             }
//         }
//     }
// }