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
#include <thread>
#include <getopt.h>
#include <math.h>
#include <atomic>
// #include <pthread.h>
// #include "threads.h"

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
    Point&          operator/=              (unsigned long long factor);
    bool            operator==              (Point &source);
    bool            operator!=              (Point &source);

    ///Arithmetic functions 
    void            negate                  ();
    void            addPoint                (Point &result, Point &B);
    void            subPoint                (Point &result, Point &B);
    void            multiplyBy2             (Point &result);
    void            multiplyByFactor        (Point &result, mpz_t &factor);
    void            divideByFactor          (Point &result, mpz_t &factor);
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

struct Port
{
    pthread_mutex_t      portLock            = PTHREAD_MUTEX_INITIALIZER;
    unsigned int         bufferWriteIndex    = 0u;
    unsigned int         bufferReadIndex     = 0u;
    unsigned int         bufferSize          = 0u;
    // pthread_mutex_t*     portLock            = nullptr;
    std::atomic_bool*    messagePresentFlag;
    unsigned int*        messageContainer    = nullptr;
    unsigned long long*  messageBuffer       = nullptr;
    
};
struct MpzBufferPort //ports used for internally transfering keys and hashes
{
    bool initialized;
    // unsigned long ownerID;
    unsigned int buffer_size = 0u;
    unsigned int buffer_number = 2u; /* The port requires at least two buffers to allow concurrent operation */
    pthread_mutex_t *locks = nullptr; /* Locks are initialized inside the port software component */
    bool *bufferFull = nullptr;
    mpz_t*** buffers;
};
struct PointBufferPort
{
    bool initialized;
    // unsigned long ownerID;
    unsigned int buffer_size = 0;
    unsigned int buffer_number = 2u; /* The port requires at least two buffers to allow concurrent operation */
    pthread_mutex_t *locks = nullptr; /* Locks are initialized inside the port software component */
    bool *bufferFull = nullptr;
    Point*** buffers;
};

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

enum ModuleBitMasks
{
    INITIALIZED_BIT_NETWORKMANAGER      = 0b0000001,
    INITIALIZED_BIT_MEMORYMANAGER       = 0b0000010,
    INITIALIZED_BIT_ITERATIONMANAGER    = 0b0000100,
    INITIALIZED_BIT_FILEMANAGER         = 0b0001000,
    INITIALIZED_BIT_FAULT               = 0b1000000,

    INITIALIZED_BIT_READY               = 0b0001111
};
struct InitDataStruct //Main file initial data
{
    char initString[512u] = "testing string initialized\n";
    std::string checkpointFileName;
    std::string knownPointsFileName;
    std::string serverAdress;
    std::string serverPort;
    unsigned int coordinatorNo;
    unsigned int workersPerCoordinator;
    unsigned int maxClientNo;
    unsigned initializedModules         = 0b0000;
    char user_input;
};

enum NetworkManager_initType
{
    NM_MODE_NONE,
    NM_MODE_SERVER,
    NM_MODE_CLIENT,
    NM_MODE_SATELLITE,
    NM_MODE_TEST
};
enum NM_ModuleBitMasks
{
    INITIALIZED_BIT_NETWORKMANAGER_NONE            = 0b00000000,
    INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO     = 0b00000001,
    INITIALIZED_BIT_NETWORKMANAGER_SERVERIP        = 0b00000010,
    INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT      = 0b00000100,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED0    = 0b00001000,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED1    = 0b00010000,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED2    = 0b00100000,
    INITIALIZED_BIT_NETWORKMANAGER_NOTASSIGNED3    = 0b01000000,
    INITIALIZED_BIT_NETWORKMANAGER_FAULT           = 0b10000000,

    INITIALIZED_BIT_NETWORKMANAGER_CLIENT_READY    = 0b00000110,
    INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY    = 0b00000111,
    INITIALIZED_BIT_NETWORKMANAGER_SATELLITE_READY = 0b00000111
};
struct NetworkManagerData
{
    Port networkManagerRxPort;
    Port *parentPort                     = nullptr;
    NetworkManager_initType functionMode = NM_MODE_NONE;
    unsigned int maxClients              = 0u;
    unsigned int coordinators            = 0u;
    unsigned int workersPerCoordinator   = 0u;
    unsigned int initializedMembers      = INITIALIZED_BIT_NETWORKMANAGER_NONE;
};

enum UI_SM_input
{
    UI_SM_RX_NONE,
    UI_SM_RX_START,
    UI_SM_RX_ABORT,
    UI_SM_RX_SHUTDOWN,
    UI_SM_RX_CONNECTION_REQUEST_CONFIRMED,
    UI_SM_RX_BUFFER_REQUEST_CONFIRMED,
    UI_SM_RX_CONTINUE,

    UI_SM_RX_NETWORK_INIT_STATE   = 0b0001,
    UI_SM_RX_FILE_INIT_STATE      = 0b0010,
    UI_SM_RX_ITERATOR_INIT_STATE  = 0b0100,
    UI_SM_RX_MEMORY_INIT_STATE    = 0b1000

};
enum UI_SM_output
{
    UI_SM_TX_NONE,
    UI_SM_TX_START_CONFIRMED,
    UI_SM_TX_SHUTDOWN_CONFIRMED,
    UI_SM_TX_REQUEST_CONNECTION,
    UI_SM_TX_REQUEST_BUFFER,
    UI_SM_TX_CONTINUING,
    UI_SM_TX_FAULT,
  
    UI_SM_TX_USERMODE_CLIENT,
    UI_SM_TX_USERMODE_SERVER,
    UI_SM_TX_USERMODE_SATELLITE,
    UI_SM_TX_USERMODE_TESTING,
    UI_SM_TX_USERMODE_EXIT,

    UI_SM_TX_USERREQUEST_START,

    UI_SM_TX_INIT_MEMMANAGER,                 
    UI_SM_TX_INIT_MEMMANAGER_KNOWNPOINTS_OK,
    UI_SM_TX_INIT_MEMMANAGER_KNOWNPOINTS_NEW,
    UI_SM_TX_INIT_MEMMANAGER_POINTPOOL_OK,
    UI_SM_TX_INIT_MEMMANAGER_POINTPOOL_NEW,

    UI_SM_TX_INIT_FILEMANAGER,                
    UI_SM_TX_INIT_FILEMANAGER_KNOWNPOINTS_OK, 
    UI_SM_TX_INIT_FILEMANAGER_KNOWNPOINTS_NEW,
    UI_SM_TX_INIT_FILEMANAGER_CHECKPOINT_OK,  
    UI_SM_TX_INIT_FILEMANAGER_CHECKPOINT_NEW, 
    UI_SM_TX_INIT_FILEMANAGER_CONNECTION_OK,  
    UI_SM_TX_INIT_FILEMANAGER_CONNECTION_NEW, 
    UI_SM_TX_INIT_FILEMANAGER_DATABASE_OK,    
    UI_SM_TX_INIT_FILEMANAGER_DATABASE_NEW,   
    UI_SM_TX_INIT_FILEMANAGER_FAULT,

    UI_SM_TX_INIT_ITERATIONMANAGER,
    UI_SM_TX_INIT_ITERATIONMANAGER_COORDNO,
    UI_SM_TX_INIT_ITERATIONMANAGER_ITERATORNO,

    UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO,
    UI_SM_TX_INIT_NETWORKMANAGER_PORT,
    UI_SM_TX_INIT_NETWORKMANAGER_IP
    
};
enum UI_SM_state
{
    UI_SM_UNINITIALIZED,
    UI_SM_INITIALIZED,
    UI_SM_RUNNING,
    UI_SM_STOPPED,
    UI_SM_FAULT
};
struct UI_SM_struct
{
    std::thread *stateMachineHandle;
    Port uiManagerRxPort;
    Port *parentPort;
    UI_SM_state SMstate;
    char user_input;
};

enum MM_ModuleBitMasks
{
    INITIALIZED_BIT_MEMMANAGER_NONE            = 0b000000000,
    INITIALIZED_BIT_MEMMANAGER_KNOWNPOINTS_OK  = 0b000000001,
    INITIALIZED_BIT_MEMMANAGER_KNOWNPOINTS_NEW = 0b000000010,
    INITIALIZED_BIT_MEMMANAGER_POINTPOOL_OK    = 0b000000100,
    INITIALIZED_BIT_MEMMANAGER_POINTPOOL_NEW   = 0b000001000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED0     = 0b000010000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED1     = 0b000100000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED2     = 0b001000000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED3     = 0b010000000,
    INITIALIZED_BIT_MEMMANAGER_FAULT           = 0b100000000,

    INITIALIZED_BIT_MEMMANAGER_CLIENT_READY    = 0b000000000,
    INITIALIZED_BIT_MEMMANAGER_SERVER_READY    = 0b000000001,
    INITIALIZED_BIT_MEMMANAGER_SATELLITE_READY = 0b000000000,
};
struct MemoryManagerData{
    Port memoryManagerRxPort;
    Port *parentPort;
    std::set<unsigned long long> *hashDatabase = nullptr;
};

enum FM_ModuleBitMasks
{
    INITIALIZED_BIT_FILEMANAGER_NONE            = 0b000000000,
    INITIALIZED_BIT_FILEMANAGER_CHECKPOINT_OK   = 0b000000001,
    INITIALIZED_BIT_FILEMANAGER_CHECKPOINT_NEW  = 0b000000010,
    INITIALIZED_BIT_FILEMANAGER_KNOWNPOINTS_OK  = 0b000000100,
    INITIALIZED_BIT_FILEMANAGER_KNOWNPOINTS_NEW = 0b000001000,
    INITIALIZED_BIT_FILEMANAGER_CONNECTION_OK   = 0b000010000,
    INITIALIZED_BIT_FILEMANAGER_CONNECTION_NEW  = 0b000100000,
    INITIALIZED_BIT_FILEMANAGER_DATABASE_OK     = 0b001000000,
    INITIALIZED_BIT_FILEMANAGER_DATABASE_NEW    = 0b010000000,
    INITIALIZED_BIT_FILEMANAGER_FAULT           = 0b100000000,
};
struct FileManagerData {

    Port fileManagerRxPort;
    Port *parentPort;
    
    std::string knownPointsFileName = "\0";
    std::ifstream *knownPointsFileInput;
    std::ofstream *knownPointsFileOutput;

    std::string connectionFileName = "\0";
    std::ifstream *connectionFileInput;
    std::ofstream *connectionFileOutput;

    std::string checkpointFileName = "\0";
    std::ifstream *checkpointFileInput;
    std::ofstream *checkpointFileOutput;

    std::string databaseFileName = "\0";
    std::ifstream *databaseFileInput;
    std::ofstream *databaseFileOutput;

    unsigned int fileManagerModules = INITIALIZED_BIT_FILEMANAGER_NONE;
};

enum IteratorSM_input//IteratorSM input commands
{
    ITERATOR_SM_RX_NONE,
    ITERATOR_SM_RX_START,
    ITERATOR_SM_RX_SHUTDOWN,
    ITERATOR_SM_RX_CONFIRM_CONNECTION_REQUEST,
    ITERATOR_SM_RX_CONFIRM_BUFFER_REQUEST,
    ITERATOR_SM_RX_CONTINUE
};
enum IteratorSM_output //IteratorSM output commands
{
    ITERATOR_SM_TX_NONE,
    ITERATOR_SM_TX_REQUEST_CONNECTION,
    ITERATOR_SM_TX_REQUEST_POINT_BUFFER
} ;
enum IteratorSM_state //IteratorSM states
{
    ITERATOR_SM_STATE_UNINITIALIZED,
    ITERATOR_SM_STATE_READY,
    ITERATOR_SM_STATE_RUNNING,
    ITERATOR_SM_STATE_WAITING,
    ITERATOR_SM_STATE_FAULT,
    ITERATOR_SM_STATE_SHUTDOWN
} ;
enum IteratorSM_algorithm //IteratorSM iteration algorithm type
{
    ITERATOR_SM_ALGORITHM_UNDEFINED,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_STEPS,
    ITERATOR_SM_ALGORITHM_SLICED_STEPS,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_MULTIPLY,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_DOUBLING,
    ITERATOR_SM_ALGORITHM_BTREE_SUBDIVISION
} ;
enum IT_ModuleBitMasks
{
    INITIALIZED_BIT_ITERATIONMANAGER_NONE          = 0b00000000,
    INITIALIZED_BIT_ITERATIONMANAGER_COORDNO       = 0b00000010,
    INITIALIZED_BIT_ITERATIONMANAGER_ITERATORNO    = 0b00000100,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED0  = 0b00001000,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED1  = 0b00010000,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED2  = 0b00100000,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED3  = 0b01000000,
    INITIALIZED_BIT_ITERATIONMANAGER_FAULT         = 0b10000000,

    INITIALIZED_BIT_ITERATIONMANAGER_READY         = 0b00000110
};
struct IteratorSM_struct //IteratorSM structure
{
    bool RxNotificationFlag; //flag signaling the presence of an incomming message
    IteratorSM_input RxFlag; /* Incomming message container */
    bool TxNotificationFlag = false; //flag signaling the presence of an outgoing message
    IteratorSM_output TxFlag; 
    unsigned int (*iterationAlgorithm)(void **args, unsigned int arg_no) = nullptr;

    Point **buffer;     //pointer to a Point buffer array. The pointer is used to allow buffer swapping by the coordinator, in order to reduce downtime
    unsigned long long errorNo; //variable holding the error code associated to the FAULT state

    IteratorSM_state SMstate = ITERATOR_SM_STATE_UNINITIALIZED;
    IteratorSM_algorithm algorithm = ITERATOR_SM_ALGORITHM_UNDEFINED;
    std::thread *stateMachineHandle;
} ;

enum CoordinatorSM_workDist
{
    COORDINATOR_SM_DISTRIBUTION_UNDEFINED,
    COORDINATOR_SM_DISTRIBUTION_VERTICAL_SYNCED,
    COORDINATOR_SM_DISTRIBUTION_HORIZONTAL_SYNCED,
    COORDINATOR_SM_DISTRIBUTION_SCATTERED
};
struct CoordinatorSM_struct //CoordinatorSM structure
{
    Port                  *memoryManagerPort  = nullptr;
    Port                  *networkManagerPort = nullptr;
    Port                  *fileManagerPort    = nullptr;
    unsigned int           workerNumber       = 0u;
    unsigned int           workerBufferSize   = 0u;
    IteratorSM_algorithm   chosenAlgorithm    = ITERATOR_SM_ALGORITHM_UNDEFINED;
    CoordinatorSM_workDist distribution       = COORDINATOR_SM_DISTRIBUTION_UNDEFINED;
    std::thread           *stateMachineHandle;

};

enum IM_ModuleBitMasks
{
    INITIALIZED_BIT_ITERATIONMANAGER_NONE            = 0b00000000,
    INITIALIZED_BIT_ITERATIONMANAGER_KNOWNPOINTS_OK  = 0b00000001,
    INITIALIZED_BIT_ITERATIONMANAGER_KNOWNPOINTS_NEW = 0b00000010,
    INITIALIZED_BIT_ITERATIONMANAGER_POINTPOOL_OK    = 0b00000100,
    INITIALIZED_BIT_ITERATIONMANAGER_POINTPOOL_NEW   = 0b00001000,
    INITIALIZED_BIT_ITERATIONMANAGER_UNASSIGNED0     = 0b00010000,
    INITIALIZED_BIT_ITERATIONMANAGER_UNASSIGNED1     = 0b00100000,
    INITIALIZED_BIT_ITERATIONMANAGER_UNASSIGNED2     = 0b01000000,
    INITIALIZED_BIT_ITERATIONMANAGER_FAULT           = 0b10000000,

    INITIALIZED_BIT_ITERATIONMANAGER_CLIENT_READY    = 0b00000110,
    INITIALIZED_BIT_ITERATIONMANAGER_SERVER_READY    = 0b00000111,
    INITIALIZED_BIT_ITERATIONMANAGER_SATELLITE_READY = 0b00000111
};
struct  IterationManagerData //IteratorManager initializer data
{
    Port iterationManagerRxPort;
    Port *parentPort;
    unsigned int coordinatorNo = 0u;
    unsigned int iteratorsPerCoordinator = 0u;
    bool managerInitialized = false;
} ;

enum  ClientHandlerStates//ClientHandlerSM states
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
};
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
enum ServerFrontendSM_input//ServerFrontendSM input messages
{
    NO_INPUT,
    START,
    PRINT_DATA,
    RESTART,
    STOP,
    SHUTDOWN
};
enum  ServerFrontendSM_output//ServerFrontendSM output messages
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

#define BUFFERED_SOCKETS 5u //the ammount of buffered sockets the frontend can hold before refusing new ones
typedef struct ServerFrontendSMStruct//ServerFrontendSM initialization data
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
};

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