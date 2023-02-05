#ifndef COMMAND_LINE_TYPE_H
#define COMMAND_LINE_TYPE_H

#include <string>

enum InstanceType {
    FLAG_OPERATION_NOOP,
    FLAG_OPERATION_CLIENT,
    FLAG_OPERATION_SERVER,
    FLAG_OPERATION_SATELLITE,
    FLAG_OPERATION_TUNELOAD
};


struct InitDataStruct //Main file initial data
{
    char initString[512u] = "testing string initialized\n";

    InstanceType instanceType = FLAG_OPERATION_NOOP;

    bool newCheckPointFile = false;    
    std::string checkpointFileName;

    bool newKnownPointsFileSize = 0u;
    std::string knownPointsFileName;
    std::string serverAdress;
    std::string serverPort;

    unsigned int memorySize = 0u;

    unsigned int coordinatorNo = 0u;
    unsigned int workersPerCoordinator;
    unsigned int maxClientNo;
    unsigned initializedModules = 0b0000;
    char user_input;
};
#endif