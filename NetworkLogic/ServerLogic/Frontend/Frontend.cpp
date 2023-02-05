#include "Frontend.h"

#include "FrontendSM/FrontendSM.h"
#include <stdio.h>

unsigned int Frontent_init()
{
    printf("Frontend initializing\n");
    FrontendSM_init();
    return 0u;
}