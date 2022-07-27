#ifndef SECP251K1_SANDBOX_DUMMY_SM_H
#define SECP251K1_SANDBOX_DUMMY_SM_H

#include "../StateMachines.h"

struct dummyStruct
{
    unsigned int dummyInt = 0u;
    char dummyBuffer[256] = {0};
    std::string dummyString;
};

void init_dummySM(dummyStruct message);

#endif