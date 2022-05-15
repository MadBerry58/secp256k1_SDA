#ifndef SECP251K1_SANDBOX_ITERATIONMANAGER_H
#define SECP251K1_SANDBOX_ITERATIONMANAGER_H
#include "../../src/headers/Point.h"

int hashGeneratorIterator(std::ofstream &outputFile, Point &startingPoint, Point &incrementPoint, Point &remainderPoint, unsigned int numberOfSlices, unsigned int pointsPerSlice);

#endif // #ifndef SECP251K1_SANDBOX_ITERATIONMANAGER_H