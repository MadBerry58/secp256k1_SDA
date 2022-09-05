#ifndef SECP251K1_SANDBOX_ALGORITHMS_H
#define SECP251K1_SANDBOX_ALGORITHMS_H

#include "../../TypeDef.h"

unsigned int checkAlgorithmParams(IteratorSM_struct iteratorData);

unsigned int hashGeneratorIterator(OutputFile &outputFile, Point &startingPoint, Point &incrementPoint, Point &remainderPoint, unsigned int numberOfSlices, unsigned int pointsPerSlice);

unsigned int init_continuousSteps();
unsigned int continuousSteps();

unsigned int init_slicedSteps();
unsigned int slicedSteps();

unsigned int init_continuousMultiply();
unsigned int continuousMultiply();

unsigned int init_continuousDoubling();
unsigned int continuousDoubling();

unsigned int init_bTreeSubdivision(void **args, unsigned int arg_no);
unsigned int bTreeSubdivision(unsigned int databaseSize, mpz_t searchPosition);

#endif // SECP251K1_SANDBOX_ALGORITHMS_H