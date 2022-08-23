#ifndef SECP251K1_SANDBOX_MEMORYMANAGER_H
#define SECP251K1_SANDBOX_MEMORYMANAGER_H

#include "../../TypeDef.h"

struct targetProfile
{
    Point targetPoint;
    Point checkOutPoint;
    mpz_t sliceSize;
    mpz_t incrementSize;
    unsigned int iterationNumber;
    unsigned int numberOfSlices;
    unsigned int pointsPerSlice;
};

struct pointsProfile
{
    Point initialPoint;
    Point finalPoint;
    mpz_t sliceSize;
    mpz_t incrementSize;
    unsigned int iterationNumber;
    unsigned int numberOfSlices;
    unsigned int pointsPerSlice;
    std::set <LSB_HASH_TYPE> knownSet;
};

int read_file_checkpoint(std::ifstream &inputFile, Point &targetPoint, Point &checkOutPoint, unsigned int iterationNumber, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);
int loadPoints(std::ifstream cardinalLSB_read, bool *listLoaded);

#endif // SECP251K1_SANDBOX_MEMORYMANAGER_H