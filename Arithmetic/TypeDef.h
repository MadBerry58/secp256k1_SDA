#ifndef SECP251K1_SANDBOX_TYPEDEF_H
#define SECP251K1_SANDBOX_TYPEDEF_H

#include <iterator>
#include <map>
#include <iostream>
#include <fstream>

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
#include <math.h>
#include <atomic>
#include <pthread.h>
// #include "threads.h"
#include <unistd.h>
#include <time.h>






































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
