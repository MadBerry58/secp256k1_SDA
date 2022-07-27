#ifndef SECP251K1_SANDBOX_ITERATORS_H
#define SECP251K1_SANDBOX_ITERATORS_H
#include "../../src/headers/Point.h"

struct algorithmParams
{
    Point target;
    mpz_t iterationMask; /* The thart position of the iteration encoded in bitmask form */

};

unsigned int checkIterationParams(unsigned int algorithmType, struct algorithmParams);

unsigned int hashGeneratorIterator(std::ofstream &outputFile, Point &startingPoint, Point &incrementPoint, Point &remainderPoint, unsigned int numberOfSlices, unsigned int pointsPerSlice);

unsigned int continuousSteps();
unsigned int slicedSteps();
unsigned int continuousMultiply();
unsigned int continuousDoubling();
unsigned int bTreeSubdivision();


#endif // SECP251K1_SANDBOX_ITERATORS_H