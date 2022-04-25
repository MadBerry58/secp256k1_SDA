#ifndef SECP251K1_SANDBOX_FILEMANAGER_H
#define SECP251K1_SANDBOX_FILEMANAGER_H
#include "../../src/headers/Operators.h"

struct targetStringProfile
{
    std::string targetPoint;
    std::string checkOutPoint;
    std::string sliceSize;
    std::string incrementSize;
    std::string iterationNumber;
    std::string numberOfSlices;
    std::string pointsPerSlice;
};

struct pointsStringProfile
{
    std::string initialPoint;
    std::string finalPoint;
    std::string sliceSize;
    std::string incrementSize;
    std::string iterationNumber;
    std::string numberOfSlices;
    std::string pointsPerSlice;
    std::set<LSB_HASH_SIZE>* knownSet;
};

void fileManager_Init();
int generationSanityCheck(Point &startingPoint, unsigned int numberOfPoints, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &incrementSize);
int generateHashedPointsFile(std::ofstream outputFile, Point &startingPoint, unsigned int numberOfPoints, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);
int generate_file_uncompressedPoints(std::ofstream outputFile, Point &startingPoint, unsigned int numberOfPoints, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);
int generate_file_checkpoint(std::ofstream outputFile, Point &targetPoint, Point &checkOutPoint, unsigned int iterationNumber, unsigned int numberOfSlices, unsigned int pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);
int checkIntegrity_file_generatedPoints(std::ifstream &inputFile);
int resumeGeneration();
int expandGeneratedList();
int createNewTargetFile(Point T, Point runningT, Point runningNT, Point temp, mpz_t &search_space);

#endif // SECP251K1_SANDBOX_FILEMANAGER_H