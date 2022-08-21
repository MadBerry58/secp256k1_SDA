#ifndef SECP251K1_SANDBOX_ALGORITHMS_H
#define SECP251K1_SANDBOX_ALGORITHMS_H

#include "../../TypeDef.h"

unsigned int checkIterationParams(unsigned int algorithmType, struct algorithmParams);

unsigned int hashGeneratorIterator(OutputFile &outputFile, Point &startingPoint, Point &incrementPoint, Point &remainderPoint, unsigned int numberOfSlices, unsigned int pointsPerSlice);

unsigned int continuousSteps();
unsigned int slicedSteps();
unsigned int continuousMultiply();
unsigned int continuousDoubling();
unsigned int bTreeSubdivision(unsigned int databaseSize, mpz_t searchPosition);

#endif // SECP251K1_SANDBOX_ALGORITHMS_H