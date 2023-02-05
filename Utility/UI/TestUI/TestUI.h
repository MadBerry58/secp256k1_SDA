#ifndef TEST_UI_H
#define TEST_UI_H

#include "../UI_Type.h"


unsigned int ArithmeticTestUI(char &user_input, std::string &user_long_input);
unsigned int AlgorithmTestUI(char &user_input, std::string &user_long_input);
unsigned int ThreadTestUI(char &user_input, std::string &user_long_input);
unsigned int NetworkTestUI(char &user_input, std::string &user_long_input);
unsigned int MemoryTestUI(char &user_input, std::string &user_long_input);
unsigned int FileTestUI(char &user_input, std::string &user_long_input);

unsigned int TestUI(char &user_input, std::string &user_long_input);

#endif