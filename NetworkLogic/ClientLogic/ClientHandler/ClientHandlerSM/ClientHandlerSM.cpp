/**
 * @file ClientHandlerSM.cpp
 * @author Mura Maxim (maxim.mura95@e-uvt.ro)
 * @brief State machine handling communication with clients
 * @version 0.1
 * @date 2022-12-03
 * 
 * @copyright Copyright (c) 2022
 * 
 * @details
 *  ClientHandlerStates: 
 *      CLIENT_HANDLER_SM_UNINITIALIZED                     - State Machine has not been initialized
 *      CLIENT_HANDLER_SM_INITIALIZED                       - State Machine is ready to connect to a client
 *      CLIENT_HANDLER_SM_RECIVED_CONNECTIONREQUEST         - A connection request has been made to the State Machine
 *      CLIENT_HANDLER_SM_AWAITINGHANDSHAKE                 - State Machine has accepted a connection request and is awaiting the unique connection code
 *      CLIENT_HANDLER_SM_CONNECTED                         - Client's connection request has been validated and the State Machine is waiting for requests
 *      CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST  - State machine is in the process of validating a progress register request
 *      CLIENT_HANDLER_SM_REGISTERING_PROGRESS              - State Machine is in the process of receiving the progress data from the client
 *      CLIENT_HANDLER_SM_DISCONNECTED                      - Client connection has been terminated
 *      CLIENT_HANDLER_SM_SHUTDOWN_REQUESTED                - State machine is processing a shutdown request
 *      CLIENT_HANDLER_SM_FAULT                             - State Machine has encountered an error and is processing it
 */

#include "ClientHandlerSM.h"

#include <time.h>

// clock_t  timePassed = 0ul;
// clock_t  timeoutVar = clock();
// uint64_t uniqueClientConnectionID = 0u; /* Confirmation code */
// uint64_t connectionConfirmationTimeout; /* Ammount of time the client has to send the correct request ID */
// uint64_t SM_watchdog_timeout;           /* Variable indicating the time for the SM's existence. If not updated periodically, SM will finish function */
// unsigned int hashBufferSize = 100u;
// ClientHandlerState SMstate = CLIENT_HANDLER_SM_UNINITIALIZED;
// bool SM_loop = false;
// unsigned int maxRetries  = 3u;
// unsigned int retryNumber = 0u;
// unsigned int challangeSize = 3 * sizeof(Point);



// ///TODO: create hash datatype
// Point **hashBuffer;
// //ComputedHash hashBuffer[hashBufferSize];

// static ClientRequests  processRequest(char *message);

// static int  messageSize = -1;
// static char *message;
// ///TODO: initialize message buffer
// static int  socketRequest = -1;
// static int  messageCode = -1;
// static int  checkSocketRequest();
// static int  checkSocketMessageBuffer(char *message);

// static bool startTimer(clock_t start, clock_t current);
// static bool checkTimer(clock_t start, clock_t current);
// static bool checkSolution(char *message);
// static bool generateChallange(char *message);
// static bool prepareBuffers();

// unsigned int init_ClientHandlerSM(clientHandlerSMStruct *messageStruct)
// {
//     unsigned int errorCode = CLIENT_HANDLER_SM_E_INIT;

//     /* Bind Client Handler Structure */
//     messageStruct->clientConnectionID = &uniqueClientConnectionID;
//     messageStruct->SMstate = (unsigned int*)(&SMstate);
//     hashBufferSize = messageStruct->bufferSize;
//     /* Allocate hash buffer */
//     messageStruct->pointBuffer = hashBuffer;

//     /* Bind communication ports */

//     /*  */
//     SMstate = CLIENT_HANDLER_SM_INITIALIZED;

//     return errorCode;
// }

// unsigned int ClientHandlerSM(clientHandlerSMStruct *messageStruct)
// {
//     unsigned int errorCode = CLIENT_HANDLER_SM_E_OK;
//     SM_loop = true;
//     while(SM_loop)
//     {
//         if(checkTimer(timeoutVar, timePassed))
//         {
//             SMstate   = CLIENT_HANDLER_SM_FAULT;
//             errorCode = CLIENT_HANDLER_SM_E_TIMEOUT;
//         }
//         else if(retryNumber > maxRetries)
//         {
//             SMstate   = CLIENT_HANDLER_SM_FAULT;
//             errorCode = CLIENT_HANDLER_SM_E_REQUEST_NR_EXCEEDED;
//         }
//         else
//         {
//             switch(SMstate)
//             {
//                 case CLIENT_HANDLER_SM_UNINITIALIZED:
//                     /* Check if SM is initialized */
//                     SMstate   = CLIENT_HANDLER_SM_FAULT;
//                     errorCode = CLIENT_HANDLER_SM_E_NO_INIT;
//                     break;

//                 case CLIENT_HANDLER_SM_INITIALIZED:
//                     /* Wait for start request */
//                     if(uniqueClientConnectionID != 0u)
//                     {
//                         SMstate = CLIENT_HANDLER_SM_WAITING_REQUEST;
//                     }
//                     else
//                     {
//                         SMstate = CLIENT_HANDLER_SM_INITIALIZED;
//                     }
//                     break;

//                 case CLIENT_HANDLER_SM_WAITING_REQUEST:
//                     /* Wait for connection request */
//                     startTimer(timeoutVar, timePassed);
//                     socketRequest = checkSocketRequest();

//                     if(socketRequest < 0u)
//                     {
//                         /* Socket error */
//                         SMstate = CLIENT_HANDLER_SM_FAULT;
//                         errorCode = CLIENT_HANDLER_SM_E_SOCKETFAULT;
//                     }
//                     else if(socketRequest > 0u)
//                     {
                        
//                         /* Process socket request */

//                     }
//                     else
//                     {
//                         /* No message received */

//                     }
//                     break;

//                 case CLIENT_HANDLER_SM_RECIVED_CONNECTIONREQUEST:
//                     /* Establish base layer connection and start a timeout for receiving the correct client connection ID */
//                     SMstate = CLIENT_HANDLER_SM_AWAITINGHANDSHAKE;
//                     break;

//                 case CLIENT_HANDLER_SM_AWAITINGHANDSHAKE:
//                     /* Process the incoming client id */
//                     messageSize = checkSocketMessageBuffer(message);
//                     if(messageSize < 0u)
//                     {
//                         /* reading socket failure */
//                         SMstate = CLIENT_HANDLER_SM_FAULT;
//                         errorCode = CLIENT_HANDLER_SM_E_SOCKETFAULT;
//                     }
//                     else if(messageSize > 0u)
//                     {
//                         /* if ID matches */
//                         SMstate = CLIENT_HANDLER_SM_CONNECTED;
//                     }
//                     else
//                     {
//                         /* no message received */
//                     }
//                     break;

//                 case CLIENT_HANDLER_SM_CONNECTED:
//                     /* The client has been connected */
//                     /* Check the message buffer for client requests */
//                     messageSize = checkSocketMessageBuffer(message);
//                     if(messageSize < 0u)
//                     {

//                     }
//                     else if(messageSize > 0u)
//                     {
//                         messageCode = processRequest(message);
//                         switch(messageCode)
//                         {
//                             case REQUEST_REGISTER_PROGRESS:
//                                 generateChallange(message);
//                                 prepareBuffers();
//                                 /* sendSocketMessage(message); */
//                                 SMstate = CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST;
//                                 break;

//                             case REQUEST_:
//                                 /* process atomic requests */
//                                 break;

//                             case REQUEST_FAULT:
//                                 SMstate = CLIENT_HANDLER_SM_FAULT;
//                                 errorCode = CLIENT_HANDLER_SM_E_BADREQUEST;
//                                 break;

//                             default:
//                                 break;
//                         }
//                     }
//                     break;

//                 case CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST:
//                     /*  Send register request */
//                         messageSize = checkSocketMessageBuffer(message);
//                         if(messageSize == challangeSize)
//                         {
//                             if(checkSolution(message))
//                             {
//                                 SMstate = CLIENT_HANDLER_SM_REGISTERING_PROGRESS;
//                             }
//                             else
//                             {
//                                 ++retryNumber;
//                             }
//                         }
//                         else if(messageSize == 0u)
//                         {
//                             /* wait to receive a message */
//                         }
//                         else if(messageSize < 0)
//                         {
//                             SMstate = CLIENT_HANDLER_SM_FAULT;
//                             errorCode = CLIENT_HANDLER_SM_E_SOCKETFAULT;
//                         }
//                         else
//                         {
//                             SMstate = CLIENT_HANDLER_SM_FAULT;
//                             errorCode = CLIENT_HANDLER_SM_E_BADREQUEST;
//                         }
//                     break;
                
//                 case CLIENT_HANDLER_SM_REGISTERING_PROGRESS:
//                     /* Receive and confirm packets */

//                     break;
                
//                 case CLIENT_HANDLER_SM_FAULT:
//                     /* Process error */
//                     switch(errorCode)
//                     {
//                         case CLIENT_HANDLER_SM_E_NO_INIT:

//                             break;

//                         case CLIENT_HANDLER_SM_E_INIT:

//                             break;

//                         case CLIENT_HANDLER_SM_E_BADREQUEST:

//                             break;

//                         case CLIENT_HANDLER_SM_E_SOCKETFAULT:

//                             break;

//                         case CLIENT_HANDLER_SM_E_INVALID_CHALLANGE_SOLUTION:

//                             break;

//                         case CLIENT_HANDLER_SM_E_CONFIRMCONNECTION:

//                             break;

//                         case CLIENT_HANDLER_SM_E_REQUEST_NR_EXCEEDED:

//                             break;

//                         case CLIENT_HANDLER_SM_E_TIMEOUT:

//                             break;  

//                         default:

//                             break;
//                     }
//                     break;
                
//                 default:
                    
//                     break;
//             }
//         }
//     }
//     /* Shutdown State Machine */

//     return errorCode;
// }