#include "DummySM.h"

void init_dummySM(dummyStruct message)
{
    std::cout << "\nDummy SM started with message: " << message.dummyString
              << "\nWith number: " << message.dummyInt
              << "\nAnd buffer:"   << message.dummyBuffer
              << std::endl;
}