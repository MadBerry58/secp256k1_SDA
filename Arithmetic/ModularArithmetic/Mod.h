#ifndef SECP251K1_SANDBOX_MOD_H
#define SECP251K1_SANDBOX_MOD_H

#include <stdlib.h>
#include <gmp.h>

/// Elliptic Curve Parameters
#define moduloHalb_String                               "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFE17"
#define order_String                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"
#define orderMinusOneDivTwo_String                      "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5D576E7357A4501DDFE92F46681B20A0"
#define prime_String                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"
#define primeMinusOne_String                            "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2E"
#define primePlusOneDivFour_String                      "3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFFF0C"
#define primePlusOneDivTwo_String                       "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFE18"
#define RANDOMNESS_SEED                                 "483ada7726a3c4655da4fbfd1e1108a8fd17b448a68554199c47d08ffb10d4b8"


unsigned int    init_Mod();
void            printConstants();

///Arithmetic functions
void neg(mpz_t &result, mpz_t &number);
void negKey(mpz_t &result, mpz_t &number);
void add(mpz_t &result, mpz_t &A, mpz_t &B);
void addKeys(mpz_t &result, mpz_t &key1, mpz_t &key2);
void sub(mpz_t &result, mpz_t &A, mpz_t &B);
void subKeys(mpz_t &result, mpz_t &A, mpz_t &B);
void mul(mpz_t &result, mpz_t &number, mpz_t &multiple);
void mulKey(mpz_t &result, mpz_t &number, mpz_t &multiple);
void div(mpz_t &result, mpz_t &number, mpz_t &divisor);
void divKey(mpz_t &result, mpz_t &number, mpz_t &divisor);
void pow(mpz_t &result, mpz_t &number, mpz_t &power);
void modSqrt(mpz_t &result, mpz_t &number);
void generateRandomKey(mpz_t &result);

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

#endif //SECP251K1_SANDBOX_MOD_H
