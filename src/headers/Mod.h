//
// Created by blackberry on 10.01.2021.

#ifndef SECP251K1_SANDBOX_MOD_H
#define SECP251K1_SANDBOX_MOD_H
#include "gmp.h"
#include "Constants.h"

void modInit();
void printConstants();

///Arithmetic functions
void neg(mpz_t &result, mpz_t &number);
void add(mpz_t &result, mpz_t &A, mpz_t &B);
void sub(mpz_t &result, mpz_t &A, mpz_t &B);
void mul(mpz_t &result, mpz_t &number, mpz_t &multiple);
void div(mpz_t &result, mpz_t &number, mpz_t &divisor);
void pow(mpz_t &result, mpz_t &number, mpz_t &power);
void addKeys(mpz_t &result, mpz_t &key1, mpz_t &key2);
void modSqrt(mpz_t &result, mpz_t &number);


#endif //SECP251K1_SANDBOX_MOD_H
