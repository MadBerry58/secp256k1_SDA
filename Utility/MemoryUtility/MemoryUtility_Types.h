#ifndef MEM_MANAGER_TYPE_H
#define MEM_MANAGER_TYPE_H

enum MM_ModuleBitMasks
{
    INITIALIZED_BIT_MEMMANAGER_NONE            = 0b000000000,
    INITIALIZED_BIT_MEMMANAGER_KNOWNPOINTS_OK  = 0b000000001,
    INITIALIZED_BIT_MEMMANAGER_KNOWNPOINTS_NEW = 0b000000010,
    INITIALIZED_BIT_MEMMANAGER_POINTPOOL_OK    = 0b000000100,
    INITIALIZED_BIT_MEMMANAGER_POINTPOOL_NEW   = 0b000001000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED0     = 0b000010000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED1     = 0b000100000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED2     = 0b001000000,
    INITIALIZED_BIT_MEMMANAGER_UNASSIGNED3     = 0b010000000,
    INITIALIZED_BIT_MEMMANAGER_FAULT           = 0b100000000,

    INITIALIZED_BIT_MEMMANAGER_CLIENT_READY    = 0b000000000,
    INITIALIZED_BIT_MEMMANAGER_SERVER_READY    = 0b000000001,
    INITIALIZED_BIT_MEMMANAGER_SATELLITE_READY = 0b000000000,
};

struct MemoryManagerData{
    // Port memoryManagerRxPort;
    // Port *parentPort;
    // std::set<unsigned long long> *hashDatabase = nullptr;
};

struct targetStringProfile
{
    // std::string targetPoint;
    // std::string checkOutPoint;
    // std::string sliceSize;
    // std::string incrementSize;
    // std::string iterationNumber;
    // std::string numberOfSlices;
    // std::string pointsPerSlice;
};

struct pointsStringProfile
{
    // std::string initialPoint;
    // std::string finalPoint;
    // std::string sliceSize;
    // std::string incrementSize;
    // std::string iterationNumber;
    // std::string numberOfSlices;
    // std::string pointsPerSlice;
    // std::set<LSB_HASH_TYPE>* knownSet;
};

struct targetProfile
{
    // Point targetPoint;
    // Point checkOutPoint;
    // mpz_t sliceSize;
    // mpz_t incrementSize;
    unsigned int iterationNumber;
    unsigned int numberOfSlices;
    unsigned int pointsPerSlice;
};

struct pointsProfile
{
    // Point initialPoint;
    // Point finalPoint;
    // mpz_t sliceSize;
    // mpz_t incrementSize;
    unsigned int iterationNumber;
    unsigned int numberOfSlices;
    unsigned int pointsPerSlice;
    // std::set <LSB_HASH_TYPE> knownSet;
};

#endif