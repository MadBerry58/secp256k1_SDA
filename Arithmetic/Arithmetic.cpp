#include "Arithmetic.h"

unsigned int InitializeArithmetic()
{
    long unsigned int errorNo = -1;
    if ((errorNo = modInit()) != MOD_E_OK)
    {
        printf("modInit failed with code %lu\n", errorNo);
    }

    if ((errorNo = pointInit()) != POINT_E_OK)
    {
        printf("pointInit failed with code %lu\n", errorNo);
    }
}