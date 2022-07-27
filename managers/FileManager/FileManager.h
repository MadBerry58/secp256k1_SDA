#ifndef SECP251K1_SANDBOX_FILEMANAGER_H
#define SECP251K1_SANDBOX_FILEMANAGER_H
#include "../managers.h"

/// File tags
#define UNCOMPRESSED_POINTS_FILE_TAG                    "UNCOMPRESSED_POINTS_FILE"
#define COMPRESSED_POINTS_FILE_TAG                      "COMPRESSED_POINTS_FILE"
#define HASHED_POINTS_FILE_TAG                          "HASH_POINTS_FILE"
#define CHECKPOINT_FILE_TAG                             "CHECKPOINT_FILE"
#define STARTING_POINT_TAG                              "STARTING_POINT"
#define TARGET_POINT_TAG                                "TARGET_POINT"
#define SLICE_NUMBER_TAG                                "NUMBER_OF_SLICES"
#define SLICE_SIZE_TAG                                  "SLICE_SIZE"
#define POINTS_PER_SLICE_TAG                            "POINTS_PER_sLICE"
#define TOTAL_POINT_NUMBER_TAG                          "TOTAL_POINTS"
#define ITERATION_NUMBER_TAG                            "ITERATION_NUMBER"
#define INCREMENT_SIZE_TAG                              "INCREMENT_SIZE"
#define EOF_TAG                                         "EOF"
#define GENERATED_POINTS_EOF_TAG                        "GENERATED_POINTS_EOF"
#define CHECKPOINT_EOF_TAG                              "CHECKPOINT_EOF"

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