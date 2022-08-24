#include "Arithmetic.h"

unsigned int InitializeArithmetic()
{
    long unsigned int errorNo = -1;
    if ((errorNo = init_Mod()) != MOD_E_OK)
    {
        printf("modInit failed with code %lu\n", errorNo);
    }

    if ((errorNo = init_Point()) != POINT_E_OK)
    {
        printf("pointInit failed with code %lu\n", errorNo);
    }
    return 0;
}