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
    void            operator*=              (mpz_t &factor);
    void            operator/=              (mpz_t &factor);
    bool            operator==              (Point &source);
    bool            operator!=              (Point &source);

    ///Arithmetic functions 
    void            negate                  ();
    void            addPoint                (Point &result, Point &B);
    void            subPoint                (Point &result, Point &B);
    void            multiplyBy2             (Point &result);
    void            multiplyByFactor        (Point &result, mpz_t &factor);

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

struct algorithmParams
{
    Point target;
    mpz_t iterationMask; /* The thart position of the iteration encoded in bitmask form */

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

struct ClientHandlerData
{
    char *clientAdressString;
    int &clientPort;
    bool &hostNotification;
    int &hostCommand;
    bool &SMnotification;
    Challange &challangeBundle;
    Solution &solutionBundle;
    ProgressPackage &progressData;
    sockaddr_in serv_addr;
};

//ClientSM input messages
//ClientSM output messages
#define CLIENT_SM_REQUEST_HANDLER "CSM_RequestHandler"
#define CLIENT_SM_REQUEST_REGISTERCHALLANGE "CSM_RequestRegisterChallange"
#define CLIENT_SM_REQUEST_REGISTERPROGRESS "CSM_RequestRegisterProgress"
#define CLIENT_SM_REQUEST_PROGRESSDATASPACE "CSM_RequestProgressDataStorageSpace"

//ClientSM states
enum ClientSMConnection
{
    CLIENT_SM_STATE_UNITIALIZED,
    CLIENT_SM_STATE_INIT,
    CLIENT_SM_STATE_REQUESTING_HANDLER,
    CLIENT_SM_STATE_CONNECTING_TO_HANDLER,
    CLIENT_SM_STATE_CONNECTED,
    CLIENT_SM_STATE_REQUESTING_PROGRESS_REGISTRATION,
    CLIENT_SM_STATE_SEND_CHALLENGE_SOLUTION,
    CLIENT_SM_STATE_SENDING_PROGRESS,
    CLIENT_SM_STATE_DISCONNECTED,
    CLIENT_SM_STATE_SHUTDOWN
};

struct clientSMStruct
{    std::string dummyData;
    Point pointBuffer[256];
};

struct clientHandlerSMStruct
{    
    std::string dummyData;
    Point pointBuffer[256];
};

struct satelliteSMStruct
{    
    std::string dummyData;
    Point pointBuffer[256];
};

struct satelliteHandlerSMStruct
{    
    std::string dummyData;
    Point pointBuffer[256];
};

struct serverSMStruct
{    
    std::string dummyData;
    Point pointBuffer[256];
};

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