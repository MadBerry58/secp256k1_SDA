#ifndef SECP251K1_SANDBOX_FILEMANAGER_H
#define SECP251K1_SANDBOX_FILEMANAGER_H
#include "../../src/headers/Iterators.h"

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
    std::set<LSB_HASH_TYPE>* knownSet;
};

unsigned int    fileManager_Init                        ();

int             generationSanityCheck                   (Point &startingPoint, unsigned long numberOfPoints, unsigned long numberOfSlices, \
                                                           unsigned long pointsPerSlice, mpz_t &incrementSize);

int             generateHashedPointsFile                (std::ofstream &outputFile, Point &startingPoint, unsigned long numberOfPoints, \
                                                           unsigned long numberOfSlices, unsigned long pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);

int             generateUncompressedPointsFile          (std::ofstream &outputFile, Point &startingPoint, unsigned long numberOfPoints, \
                                                           unsigned long numberOfSlices, unsigned long pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);

int             generate_file_checkpoint                (std::ofstream &outputFile, Point &targetPoint, Point &checkOutPoint, unsigned long &iterationNumber, \
                                                           unsigned long &numberOfSlices, unsigned long &pointsPerSlice, mpz_t &sliceSize, mpz_t &incrementSize);

int             checkIntegrity_file_checkpoint          (std::ifstream &inputFile, Point &output_targetPoint, Point &output_checkOutPoint, unsigned long &output_iterationNumber, \
                                                        unsigned long &output_numberOfSlices, unsigned long &output_pointsPerSlice, mpz_t &output_sliceSize, mpz_t &output_incrementSize, \
                                                        bool writeToParameters = false);

int             resumeGeneration                        ();

int             expandGeneratedList                     ();

int             createNewTargetFile                     (Point T, Point runningT, Point runningNT, Point temp, mpz_t &search_space);

#endif // SECP251K1_SANDBOX_FILEMANAGER_H