#include "Arithmetic.h"

#include "../Utility/GlobalData/ErrorCodes.h"
#include "../Utility/GlobalData/Definitions.h"

unsigned int Arithmetic_Init()
{
    long unsigned int errorNo = 0;
    if ((errorNo = init_Mod()) != MOD_E_OK)
    {
        printf("modInit failed with code %lu\n", errorNo);
    }
    else
    if ((errorNo = init_Point()) != POINT_E_OK)
    {
        printf("pointInit failed with code %lu\n", errorNo);
    }
    return errorNo;
}