#ifndef FILE_MANAGER_TYPE_H
#define FILE_MANAGER_TYPE_H

#include <fstream>

enum FM_ModuleBitMasks
{
    INITIALIZED_BIT_FILEMANAGER_NONE            = 0b000000000,
    INITIALIZED_BIT_FILEMANAGER_CHECKPOINT_OK   = 0b000000001,
    INITIALIZED_BIT_FILEMANAGER_CHECKPOINT_NEW  = 0b000000010,
    INITIALIZED_BIT_FILEMANAGER_KNOWNPOINTS_OK  = 0b000000100,
    INITIALIZED_BIT_FILEMANAGER_KNOWNPOINTS_NEW = 0b000001000,
    INITIALIZED_BIT_FILEMANAGER_CONNECTION_OK   = 0b000010000,
    INITIALIZED_BIT_FILEMANAGER_CONNECTION_NEW  = 0b000100000,
    INITIALIZED_BIT_FILEMANAGER_DATABASE_OK     = 0b001000000,
    INITIALIZED_BIT_FILEMANAGER_DATABASE_NEW    = 0b010000000,
    INITIALIZED_BIT_FILEMANAGER_FAULT           = 0b100000000,
};

struct FileManagerData {

    // Port fileManagerRxPort;
    // Port *parentPort;
    
    std::string knownPointsFileName = "\0";
    std::ifstream *knownPointsFileInput;
    std::ofstream *knownPointsFileOutput;

    std::string connectionFileName = "\0";
    std::ifstream *connectionFileInput;
    std::ofstream *connectionFileOutput;

    std::string checkpointFileName = "\0";
    std::ifstream *checkpointFileInput;
    std::ofstream *checkpointFileOutput;

    std::string databaseFileName = "\0";
    std::ifstream *databaseFileInput;
    std::ofstream *databaseFileOutput;

    unsigned int fileManagerModules = INITIALIZED_BIT_FILEMANAGER_NONE;
};

#endif