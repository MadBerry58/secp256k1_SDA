#ifndef COMMAND_LINE_PARSING
#define COMMAND_LINE_PARSING

#include "CommandLine_Types.h"

uint64_t parseArguments(int argc, char **argv, std::string &returnMessage, InitDataStruct &initData);

#endif