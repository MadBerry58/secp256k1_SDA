#ifndef SECP251K1_SANDBOX_TYPEDEF_H
#define SECP251K1_SANDBOX_TYPEDEF_H

#include "Constants.h"

#include <gmp.h>
#include <iterator>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <cstring>
#include <time.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
// #include <thread>
#include <getopt.h>
#include <math.h>
#include <atomic>
#include <atomic>
#include <pthread.h>
// #include "threads.h"
#include <unistd.h>
typedef std::ofstream OutputFile;

class Point
{
private:
    mpz_t           k;
    mpz_t           x;
    mpz_t           y;
    mpz_t           t1;
    mpz_t           t2;
    mpz_t           m;
    mpz_t           n;
    bool            keyKnown = false;
    char            outputString[100];

public: 
    ///Initializer functions    
                    Point                   ();
                    Point                   (mpz_t &key);
                    Point                   (Point &source);
                    Point                   (const char *xString, const char *yString);
                    Point                   (const char *xString, const char *yString,const char *kString);
                    ~Point                  ();

    ///Overloaded operators 
    void            operator=               (Point &source);
    void            operator=               (mpz_t &key);
    void            operator=               (char  *keyString);
    Point&          operator-=              (Point &source);
    Point&          operator+=              (Point &source);
    Point&          operator*=              (mpz_t &factor);
    Point&          operator*=              (unsigned long long factor);
    Point&          operator/=              (mpz_t &factor);
    bool            operator==              (Point &source);
    bool            operator!=              (Point &source);

    ///Arithmetic functions 
    void            negate                  ();
    void            addPoint                (Point &result, Point &B);
    void            subPoint                (Point &result, Point &B);
    void            multiplyBy2             (Point &result);
    void            multiplyByFactor        (Point &result, mpz_t &factor);
    void            multiplyByFactor        (Point &result, unsigned long long &factor);

    ///Getters  
    char*           getX                    ();
    char*           getY                    ();
    char*           getK                    ();
    LSB_HASH_TYPE   getLSB                  ();

    ///Setters  
    void            setK                    (const char *k, int base, bool known);
    void            setX                    (const char *x, int base);
    void            setY                    (const char *y, int base);
    void            reset                   ();
    void            setFromK                (const char *kValue, int base); 

    ///Printout functions   
    void            printPointInfo          ();
    void            printDec                ();
    void            printHex                ();

    ///Utility functions    
    bool            checkY                  ();
    char*           generateY               ();
    bool            isKeyKnown              ();

    ///Testing functions
    void            toggleKeyKnowledgeState ();
};

class JPoint{
public:
                    JPoint              (char *x, char *y, char *z);
    void            addPoint            (Point &result, Point &B);
    void            printDec            ();
    void            printHex            ();
    char*           getX                ();
    char*           getY                ();
    char*           getK                ();
    unsigned long long int getLSB();
private:
    mpz_t           x;
    mpz_t           y;
    mpz_t           z;
};

struct BigNumber
{
    private:
        mpz_t value;

    public:
       inline BigNumber();
       inline BigNumber(char *numberString);
       inline ~BigNumber();
       inline void operator=(mpz_t &source);
       inline void operator=(char *sourceString);
       inline void operator=(unsigned long long &sourceInteger);
       inline void operator+=(mpz_t &source);
       inline void operator+=(char *sourceString);
       inline void operator+=(unsigned long long &sourceInteger);
       inline void operator-=(mpz_t &source);
       inline void operator-=(char *sourceString);
       inline void operator-=(unsigned long long &sourceInteger);
       inline void operator*=(mpz_t &source);
       inline void operator*=(char *sourceString);
       inline void operator*=(unsigned long long &sourceInteger);
       inline void operator/=(mpz_t &source);
       inline void operator/=(char *sourceString);
       inline void operator/=(unsigned long long &sourceInteger);
       inline void operator^=(mpz_t &source);
       inline void operator^=(char *sourceString);
       inline void operator^=(unsigned long long &sourceInteger);
       inline bool operator==(mpz_t &source);
       inline bool operator==(unsigned long long &sourceInteger);
       inline bool operator<(mpz_t &source);
       inline bool operator<(unsigned long long &sourceInteger);
       inline bool operator>(mpz_t &source);
       inline bool operator>(unsigned long long &sourceInteger);
       inline mpz_t& getValuePointer();
};

#define PORT_EMPTY        0u
#define PORT_MESSAGE_READ 1u
#define PORT_MESSAGE_SENT 2u
#define PORT_BUSY         3u
typedef struct
{
    pthread_mutex_t      portLock            = PTHREAD_MUTEX_INITIALIZER;
    unsigned int         bufferWriteIndex    = 0u;
    unsigned int         bufferReadIndex     = 0u;
    unsigned int         bufferSize          = 0u;
    // pthread_mutex_t*     portLock            = nullptr;
    std::atomic_bool*    messagePresentFlag;
    unsigned int*        messageContainer    = nullptr;
    unsigned long long*  messageBuffer       = nullptr;
    
} Port;

struct targetStringProfile
{
    std::string targetPoint;
    std::string checkOutPoint;
    std::string sliceSize;
    std::string incrementSize;
    std::string iterationNumber;
    std::string numberOfSlices;
    std::string pointsPerSlice;
};
struct pointsStringProfile
{
    std::string initialPoint;
    std::string finalPoint;
    std::string sliceSize;
    std::string incrementSize;
    std::string iterationNumber;
    std::string numberOfSlices;
    std::string pointsPerSlice;
    std::set<LSB_HASH_TYPE>* knownSet;
};
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

#define ITERATOR_SM_RETRY_COUNT 3u
#define ITERATOR_SM_RETRY_DELAY 0.4

typedef struct //Main file initial data
{
    char initString[512u] = "testing string initialized\n";
    std::string checkpointFileName;
    std::string knownPointsFileName;
    std::string serverAdress;
    std::string serverPort;
    char user_input;
} InitDataStruct;

typedef struct //IteratorManager initializer data
{
    Port iterationManagerRxPort;
    Port *parentPort;
    unsigned int iteratorNumber = 0;

}IterationManagerData;

typedef struct 
{
    Port networkManagerRxPort;
    Port *parentPort;
}NetworkManagerData;

typedef enum
{
    UI_UNINITIALIZED,
    UI_RUNNING,
    UI_STOPPED,
    UI_FAULT
} UserInterfaceState;
typedef struct {
    std::thread *stateMachineHandle;
    Port uiManagerRxPort;
    Port *parentPort;
    UserInterfaceState SMstate;
    char user_input;
}UISMStruct;

typedef struct {
    Port memoryManagerRxPort;
    Port *parentPort;
}MemoryManagerData;

typedef struct {
    Port fileManagerRxPort;
    Port *parentPort;
}FileManagerData;

typedef enum //ITERATOR_SM input commands
{
    ITERATOR_SM_RX_NONE,
    ITERATOR_SM_RX_START,
    ITERATOR_SM_RX_SHUTDOWN,
    ITERATOR_SM_RX_CONFIRM_CONNECTION_REQUEST,
    ITERATOR_SM_RX_CONFIRM_BUFFER_REQUEST,
    ITERATOR_SM_RX_CONTINUE
}IteratorSM_input;
typedef enum //IteratorSM output commands
{
    ITERATOR_SM_TX_NONE,
    ITERATOR_SM_TX_REQUEST_CONNECTION,
    ITERATOR_SM_TX_REQUEST_POINT_BUFFER
}IteratorSM_output;
typedef enum //ITERATOR_SM states
{
    ITERATOR_SM_STATE_UNINITIALIZED,
    ITERATOR_SM_STATE_READY,
    ITERATOR_SM_STATE_RUNNING,
    ITERATOR_SM_STATE_WAITING,
    ITERATOR_SM_STATE_FAULT,
    ITERATOR_SM_STATE_SHUTDOWN
} IteratorSMState;
typedef enum //IteratorSM iteration algorithm type
{
    ITERATOR_SM_ALGORITHM_UNDEFINED,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_STEPS,
    ITERATOR_SM_ALGORITHM_SLICED_STEPS,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_MULTIPLY,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_DOUBLING,
    ITERATOR_SM_ALGORITHM_BTREE_SUBDIVISION
} IteratorSM_Algorithm;
typedef struct //ITERATOR_SM structure
{
    bool RxNotificationFlag; //flag signaling the presence of an incomming message
    IteratorSM_input RxFlag; /* Incomming message container */
    bool TxNotificationFlag = false; //flag signaling the presence of an outgoing message
    IteratorSM_output TxFlag; 
    unsigned int (*iterationAlgorithm)(void **args, unsigned int arg_no) = nullptr;

    Point **buffer;     //pointer to a Point buffer array. The pointer is used to allow buffer swapping by the coordinator, in order to reduce downtime
    unsigned long long errorNo; //variable holding the error code associated to the FAULT state

    IteratorSMState SMstate = ITERATOR_SM_STATE_UNINITIALIZED;
    IteratorSM_Algorithm algorithm = ITERATOR_SM_ALGORITHM_UNDEFINED;
    std::thread *stateMachineHandle;
} IteratorSMStruct;

typedef enum
{
    COORDINATOR_SM_DISTRIBUTION_UNDEFINED,
    COORDINATOR_SM_DISTRIBUTION_VERTICAL_SYNCED,
    COORDINATOR_SM_DISTRIBUTION_HORIZONTAL_SYNCED,
    COORDINATOR_SM_DISTRIBUTION_SCATTERED
}CoordinatorSM_workDist;
typedef struct //CoordinatorSM structure
{
    Port                  *memoryManagerPort  = nullptr;
    Port                  *networkManagerPort = nullptr;
    Port                  *fileManagerPort    = nullptr;
    unsigned int           workerNumber       = 0u;
    unsigned int           workerBufferSize   = 0u;
    IteratorSM_Algorithm   chosenAlgorithm    = ITERATOR_SM_ALGORITHM_UNDEFINED;
    CoordinatorSM_workDist distribution       = COORDINATOR_SM_DISTRIBUTION_UNDEFINED;
    std::thread           *stateMachineHandle;

}CoordinatorSMStruct;

typedef enum //ClientHandlerSM states
{
    CLIENT_HANDLER_SM_UNINITIALIZED,
    CLIENT_HANDLER_SM_INITIALIZING,
    CLIENT_HANDLER_SM_INITIALIZED,
    CLIENT_HANDLER_SM_AWAITINGHANDSHAKE,
    CLIENT_HANDLER_SM_RECIVED_CONNECTIONREQUEST,
    CLIENT_HANDLER_SM_CONNECTED,
    CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST,
    CLIENT_HANDLER_SM_REGISTERING_PROGRESS,
    CLIENT_HANDLER_SM_DISCONNECTED,
    CLIENT_HANDLER_SM_SHUTDOWN_REQUESTED
} ClientHandlerStates;
struct clientHandlerSMStruct
{    
    std::string dummyData;
    ClientHandlerStates SMstate = CLIENT_HANDLER_SM_UNINITIALIZED;
    Point pointBuffer[256];
    std::thread *stateMachineHandle;
};

struct clientSMStruct
{   
    std::string dummyData;
    Point pointBuffer[256];
    std::thread *stateMachineHandle;
};
struct satelliteSMStruct
{    
    std::string dummyData;
    Point pointBuffer[256];
    std::thread *stateMachineHandle;
};
struct satelliteHandlerSMStruct
{    
    std::string dummyData;
    Point pointBuffer[256];
    std::thread *stateMachineHandle;
};

////ServerFrontendSM protocol data
typedef enum //ServerFrontendSM input messages
{
    NO_INPUT,
    START,
    PRINT_DATA,
    RESTART,
    STOP,
    SHUTDOWN
} ServerFrontendSM_input;
typedef enum //ServerFrontendSM output messages
{
    NO_OUTPUT,
    SOCKET_AVAILABLE
} ServerFrontendSM_output;
typedef enum //ServerFrontendSM states
{
    UNINITIALIZED,
    INITIALIZING,
    INITIALIZED,
    LISTENING,
    CHECK_REQUESTBUFFER,
    FAULT,
    CLIENT_CONNECTION_REQUESTED,
    SHUTDOWN_REQUESTED
} ServerFrontendSM_state;
#define BUFFERED_SOCKETS 5u //the ammount of buffered sockets the frontend can hold before refusing new ones
typedef struct //ServerFrontendSM initialization data
{
    std::string dummyData;
    int server_tcp_port = -1;
    char serverHostName[MAXHOSTNAMELEN] = {0};
    struct hostent *he;
    struct sockaddr_in serv_addr;
    int sockfd = -1;
    char *ServerName;
    bool bindedSM = false;
    ServerFrontendSM_input inputMessage; //will have to be made platform independent
    ServerFrontendSM_output outputMessage;
    
    struct sockaddr_in cli_addr;
    socklen_t clilen;
    int newsockfd;
    char line[MAX_MESSAGE_LINE];

    ServerFrontendSM_state SMstate = UNINITIALIZED;
    unsigned int error = 0u;

    std::thread *stateMachineHandle;
}ServerFrontendSMStruct;




#define ECHO            65534u
#define ECHO_RESPONSE   65535u

/// Function-like macros
#ifdef DEBUG
#define DEBUG_MSG(...)                          gmp_printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)                          
#endif

#ifdef TARGET_DEBUG
#define TARGET_DEBUG_MSG(...)                   gmp_printf(__VA_ARGS__)
#else
#define TARGET_DEBUG_MSG(...)
#endif

#endif
