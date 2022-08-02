#ifndef SECP251K1_SANDBOX_TESTUI_H
#define SECP251K1_SANDBOX_TESTUI_H

#include "../../../TypeDef.h"


unsigned int ArithmeticTestUI(char &user_input, std::string &user_long_input);
unsigned int AlgorithmTestUI(char &user_input, std::string &user_long_input);
unsigned int ThreadTestUI(char &user_input, std::string &user_long_input);
unsigned int NetworkTestUI(char &user_input, std::string &user_long_input);
unsigned int MemoryTestUI(char &user_input, std::string &user_long_input);
unsigned int FileTestUI(char &user_input, std::string &user_long_input);

unsigned int TestUI(char &user_input, std::string &user_long_input);
#endif