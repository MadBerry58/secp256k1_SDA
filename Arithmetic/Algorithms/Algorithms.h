#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../PointArithmetic/Point.h"
#include "../ModularArithmetic/Mod.h"

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

#endif