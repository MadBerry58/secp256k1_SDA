#ifndef SECP251K1_SANDBOX_THREADMANAGER_H
#define SECP251K1_SANDBOX_THREADMANAGER_H
#include "../../src/headers/Point.h"
#include "../../src/headers/Iterators.h"
#include "threads.h"
#include <pthread.h>

int createThread();

int initThread();

int testThread();

int testWorkoad();

int solveChallange();

#endif // SECP251K1_SANDBOX_THREADMANAGER_H