//
// Created by blackberry on 25.01.2021.
//

#ifndef SECP251K1_SANDBOX_OPERATORS_H
#define SECP251K1_SANDBOX_OPERATORS_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include "Point.h"

///Using the main function as a central controller, Operator objects contain all the containers necessary for independent iterations

void saveMatch();
void generateLeastSignificantBits();
void loadLeastSignificantBits(char *filename, std::ofstream cardinalLSB_read, std::set<unsigned long int> LSB_cardinal);
void saveCheckpoint();
void loadCheckpoint();

void generateExplicititCardinalList();
bool regenerateAddedPoint();

class Operator{
private:
    static std::set<unsigned long> *cardinalLSBlist;
    Point G;
    Point temp;
    Point target;
    Point negativeTarget;
    Point runningTarget;
    Point runningNegativeTarget;
    Point backJump;
    Point jump;
    Point subJump;

    bool loadCheckpoint(char *fileName);
    bool saveCheckpoint();
public:
    Operator();
    Operator(char *fileName);
    Operator(char *targetX, char *targetY, mpz_t iteration, int jump);
    int iterate(int iterations);
    void extractKey(mpz_t &output, mpz_t iteration, int jump, int subjump);
    bool bindCardinalLSB(std::set<unsigned long> &generatedList);

};
#endif //SECP251K1_SANDBOX_OPERATORS_H
