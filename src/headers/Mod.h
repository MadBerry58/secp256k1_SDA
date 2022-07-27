//
// Created by blackberry on 10.01.2021.

#ifndef SECP251K1_SANDBOX_MOD_H
#define SECP251K1_SANDBOX_MOD_H
#include <gmp.h>
#include "Constants.h"
#include <iterator>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <cstring>
#include <time.h>

unsigned int    modInit();
void            printConstants();

struct BigNumber
{
    private:
        mpz_t value;

    public:
       inline BigNumber();
       inline BigNumber(char *numberString);
       inline ~BigNumber();
       inline void operator=(mpz_t &source);
       inline void operator=(char *sourceString);
       inline void operator=(unsigned long long &sourceInteger);
       inline void operator+=(mpz_t &source);
       inline void operator+=(char *sourceString);
       inline void operator+=(unsigned long long &sourceInteger);
       inline void operator-=(mpz_t &source);
       inline void operator-=(char *sourceString);
       inline void operator-=(unsigned long long &sourceInteger);
       inline void operator*=(mpz_t &source);
       inline void operator*=(char *sourceString);
       inline void operator*=(unsigned long long &sourceInteger);
       inline void operator/=(mpz_t &source);
       inline void operator/=(char *sourceString);
       inline void operator/=(unsigned long long &sourceInteger);
       inline void operator^=(mpz_t &source);
       inline void operator^=(char *sourceString);
       inline void operator^=(unsigned long long &sourceInteger);
       inline bool operator==(mpz_t &source);
       inline bool operator==(unsigned long long &sourceInteger);
       inline bool operator<(mpz_t &source);
       inline bool operator<(unsigned long long &sourceInteger);
       inline bool operator>(mpz_t &source);
       inline bool operator>(unsigned long long &sourceInteger);
       inline mpz_t& getValuePointer();
};
///Arithmetic functions
void neg(mpz_t &result, mpz_t &number);
void add(mpz_t &result, mpz_t &A, mpz_t &B);
void sub(mpz_t &result, mpz_t &A, mpz_t &B);
void mul(mpz_t &result, mpz_t &number, mpz_t &multiple);
void div(mpz_t &result, mpz_t &number, mpz_t &divisor);
void pow(mpz_t &result, mpz_t &number, mpz_t &power);
void addKeys(mpz_t &result, mpz_t &key1, mpz_t &key2);
void modSqrt(mpz_t &result, mpz_t &number);
void generateRandomKey(mpz_t &result);


#endif //SECP251K1_SANDBOX_MOD_H
