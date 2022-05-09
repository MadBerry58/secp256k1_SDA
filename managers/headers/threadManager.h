#ifndef SECP251K1_SANDBOX_THREADMANAGER_H
#define SECP251K1_SANDBOX_THREADMANAGER_H
#include "../../src/headers/Operators.h"
#include "iterationManager.h"
#include "threads.h"
#include <pthread.h>

int createThread();

int initThread();

int testThread();

int testWorkoad();

int solveChallange();

#endif // SECP251K1_SANDBOX_THREADMANAGER_H