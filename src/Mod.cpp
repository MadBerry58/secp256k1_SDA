//
// Created by blackberry on 10.01.2021.
//

#include "../include/Mod.h"
mpz_t moduloHalb;
mpz_t order;
mpz_t prime;
mpz_t primeMinusOne;
mpz_t primePlusOneDivFour;
mpz_t zero;
mpz_t one;
mpz_t two;
mpz_t three;
mpz_t four;
mpz_t five;
mpz_t six;
mpz_t seven;
mpz_t t1;
mpz_t t2;

void modInit(){
    mpz_init_set_str(moduloHalb, "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFE17", 16);
    mpz_init_set_str(order, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141", 16);
    mpz_init_set_str(prime, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", 16);
    mpz_init_set_str(primeMinusOne, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2E", 16);
    mpz_init_set_str(primePlusOneDivFour, "3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFFF0C", 16);
    mpz_init_set_d(zero, 0);
    mpz_init_set_d(one, 1);
    mpz_init_set_d(two, 2);
    mpz_init_set_d(three, 3);
    mpz_init_set_d(four, 4);
    mpz_init_set_d(five, 5);
    mpz_init_set_d(six, 6);
    mpz_init_set_d(seven, 7);
    mpz_init_set_d(t1, 0);
    mpz_init_set_d(t2, 0);

}
void printConstants(){
    gmp_printf("\nPrime: %Zx \nOrder: %Zx", prime, order);
}
void neg(mpz_t &result, mpz_t &number){
    mpz_sub(result, prime, number);
}
void add(mpz_t &result, mpz_t &A, mpz_t &B){
    mpz_add(t1, A, B);
    mpz_mod(result, t1, prime);
}
void sub(mpz_t &result, mpz_t &A, mpz_t &B){
    neg(t1, B);
    add(result, A, t1);
}
void mul(mpz_t &result, mpz_t &number, mpz_t &multiple){
    mpz_mul(t1, number, multiple);
    mpz_mod(result, t1, prime);
}
void div(mpz_t &result, mpz_t &number, mpz_t &divisor){
    mpz_invert(t1, divisor, prime);
    mpz_mul(t2, number, t1);
    mpz_mod(result, t2, prime);
}
void pow(mpz_t &result, mpz_t &number, mpz_t &power){
    mpz_powm(result, number, power, prime);
}
void modSqrt(mpz_t &result, mpz_t &number){
     ///Tonelli–Shanks algorithm - since the prime always results in s = 1, only one branch of the algorithm is needed
     pow(t1, number, primePlusOneDivFour);
     pow(t2, t1, two);
     if(mpz_cmp(t2, number) == 0){
         mpz_set(result, t1);
     }else{
         mpz_set(result, zero);
     }
}

void addKeys(mpz_t &result, mpz_t &key1, mpz_t &key2){
    mpz_add(t1, key1, key2);
    mpz_mod(result, t1, order);
}