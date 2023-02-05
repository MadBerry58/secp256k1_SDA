#ifndef FRONTEND_TYPES_H
#define FRONTEND_TYPES_H

enum ServerFrontendSM_input//ServerFrontendSM input messages
{
    NO_INPUT,
    START,
    PRINT_DATA,
    RESTART,
    STOP,
    SHUTDOWN
};

enum ServerFrontendSM_output//ServerFrontendSM output messages
{
    NO_OUTPUT,
    SOCKET_AVAILABLE
};

enum ServerFrontendSM_state//ServerFrontendSM states
{
    UNINITIALIZED,
    INITIALIZING,
    INITIALIZED,
    LISTENING,
    CHECK_REQUESTBUFFER,
    FAULT,
    CLIENT_CONNECTION_REQUESTED,
    SHUTDOWN_REQUESTED
};

struct ServerFrontendSM_struct//ServerFrontendSM initialization data
{
    // std::string dummyData;
    int server_tcp_port = -1;
    // char serverHostName[MAXHOSTNAMELEN] = {0};
    // struct hostent *he;
    // struct sockaddr_in serv_addr;
    // int sockfd = -1;
    // char *ServerName;
    // bool bindedSM = false;
    // ServerFrontendSM_input inputMessage; //will have to be made platform independent
    // ServerFrontendSM_output outputMessage;
    
    // struct sockaddr_in cli_addr;
    // socklen_t clilen;
    // int newsockfd;
    // char line[MAX_MESSAGE_LINE];

    // ServerFrontendSM_state SMstate = UNINITIALIZED;
    // unsigned int error = 0u;

    // std::thread *stateMachineHandle;
};

#endif