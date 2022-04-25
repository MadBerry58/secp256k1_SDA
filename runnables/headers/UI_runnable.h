#ifndef SECP251K1_SANDBOX_UIRUNNABLE_H
#define SECP251K1_SANDBOX_UIRUNNABLE_H
#include "../../src/headers/Operators.h"

static char counterOutput[1024];
static char user_input = 's';

int userInterface_Init();
int userInterface_Start();

#endif // SECP251K1_SANDBOX_UIRUNNABLE_H