//
// Created by blackberry on 10.01.2021.
//

#include "headers/Mod.h"

///Leave this here or everything goes to shit
mpz_t moduloHalb;
mpz_t order;
mpz_t orderHalf;
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
gmp_randstate_t randomState;
mpz_t randomSeed;

///TODO: check if using t as an intermediary container offers speed benefits

unsigned int modInit() 
{
    DEBUG_MSG("Initializing Modular library \n");

    mpz_init_set_str(moduloHalb, moduloHalb_String, PREFFERED_BASE);
    mpz_init_set_str(order, order_String, PREFFERED_BASE);
    mpz_init_set_str(prime, prime_String, PREFFERED_BASE);
    mpz_init_set_str(primeMinusOne, primeMinusOne_String, PREFFERED_BASE);
    mpz_init_set_str(primePlusOneDivFour, primePlusOneDivFour_String, PREFFERED_BASE);
    mpz_init_set_str(orderHalf, orderMinusOneDivTwo_String, PREFFERED_BASE);
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


    if (mpz_cmp_ui(seven, 7) != 0)
    {
        DEBUG_MSG("MPZ initialization failed \n");
        return MOD_E_MPZ_ASSIGNMENT_INVALID;
    }
    mpz_add(t1, primeMinusOne, one);
    if (mpz_cmp(t1, prime) != 0)
    {
        DEBUG_MSG("MPZ addition failed \n");
        
        return MOD_E_MPZ_ADDITION_INVALID;
    }

    DEBUG_MSG("MPZ functionality works\n");

    DEBUG_MSG("Initializing random number variables\n");
    
    gmp_randinit_mt(randomState);
    mpz_init_set_str(randomSeed, RANDOMNESS_SEED, PREFFERED_BASE);
    gmp_randseed(randomState, randomSeed);
    
    DEBUG_MSG("Random number variables initalized successfully\n");

    DEBUG_MSG("Testing Mod addition \n");

    add(t1, primeMinusOne, six);
    if (mpz_cmp(t1, five) != 0)
    {
        DEBUG_MSG("Mod addition failed \n");
        return MOD_E_MOD_ADDITION_INVALID;
    }

    DEBUG_MSG("Testing Mod subtraction \n");
    
    sub(t1, six, two);
    if (mpz_cmp(t1, four) != 0)
    {
        DEBUG_MSG("Mod subtraction failed \n");
        return MOD_E_MOD_SUBTRACTION_INVALID;
    }

    DEBUG_MSG("Testing Mod Square Root \n");

    modSqrt(t1, six);

    DEBUG_MSG("Square root of 6: %Zd \n", t1);

    if (mpz_cmp_ui(t1, 0u) != 0)
    {
        DEBUG_MSG("Mod squareRoot 0 failed \n");
        return MOD_E_MOD_SUBTRACTION_INVALID;
    }

    /// Power function does not work with the same return parameter as the multiplicands
    mpz_urandomb(t1, randomState, 250u);
    pow(t2, t1, two);
    modSqrt(t1, t2);
    if (mpz_cmp_ui(t1, 0u) == 0)
    {
        DEBUG_MSG("Mod squareRoot %Zu failed \n", t2);
        return MOD_E_MOD_SQUAREROOT_INVALID;
    }

    DEBUG_MSG("              X: %Zu \n", t2);
    DEBUG_MSG("sqare root pf X: %Zu \n", t1);

    DEBUG_MSG("Mod functionality correctly initialized \n");

    printf("Mod OK \n");

    return MOD_E_OK;
}

inline BigNumber::BigNumber()
{
    mpz_init_set_ui(value, 0);
}

inline BigNumber::BigNumber(char *numberString)
{
    mpz_init_set_str(value, numberString, PREFFERED_BASE);
}

inline void BigNumber::operator=(mpz_t &source)
{
    mpz_set(value, source);
}

inline void BigNumber::operator=(char *sourceString)
{
    mpz_set_str(value, sourceString, PREFFERED_BASE);
}

inline void BigNumber::operator=(unsigned long long &sourceInteger)
{
    mpz_set_ui(value, sourceInteger);
}

inline void BigNumber::operator+=(mpz_t &source)
{
    mpz_add(value, value, source);
    mpz_mmod(value, value, prime);
}

inline void BigNumber::operator+=(char *sourceString)
{
    mpz_set_str(t1, sourceString, PREFFERED_BASE);
    mpz_add(value, value, t1);
    mpz_mmod(value, value, prime);
}

inline void BigNumber::operator+=(unsigned long long &sourceInteger)
{
    mpz_add_ui(value, value, sourceInteger);
    mpz_mmod(value, value, prime);
}

inline void BigNumber::operator-=(mpz_t &source)
{
    mpz_sub(t2, prime, t1);
    mpz_add(value, value, t2);
    mpz_mmod(value, value, prime);
}

inline void BigNumber::operator-=(char *sourceString)
{
    mpz_set_str(t1, sourceString, PREFFERED_BASE);
    mpz_sub(t2, prime, t1);
    mpz_add(value, value, t2);
    mpz_mmod(value, value, prime);
}

inline void BigNumber::operator-=(unsigned long long &sourceInteger)
{
    mpz_sub_ui(t2, prime, sourceInteger);
    mpz_add(value, value, t2);
    mpz_mmod(value, value, prime);
}

inline void BigNumber::operator*=(mpz_t &source)
{
    mpz_mul(t1, value, source);
    mpz_mmod(value, t1, prime);
}

inline void BigNumber::operator*=(char *sourceString)
{
    mpz_set_str(t1, sourceString, PREFFERED_BASE);
    mpz_mul(t2, value, t1);
    mpz_mmod(value, t2, prime);
}

inline void BigNumber::operator*=(unsigned long long &sourceInteger)
{
    mpz_mul_ui(t1, value, sourceInteger);
    mpz_mmod(value, t1, prime);
}

inline void BigNumber::operator/=(mpz_t &source)
{
    mpz_invert(t1, source, prime);
    mpz_mul(t2, value, t1);
    mpz_mmod(value, t2, prime);
}

inline void BigNumber::operator/=(char *sourceString)
{
    mpz_set_str(t1, sourceString, PREFFERED_BASE);
    mpz_invert(t2, t1, prime);
    mpz_mul(t1, value, t2);
    mpz_mmod(value, t1, prime);
}

inline void BigNumber::operator/=(unsigned long long &sourceInteger)
{
    mpz_set_ui(t1, sourceInteger);
    mpz_invert(t2, t1, prime);
    mpz_mul(t1, value, t2);
    mpz_mmod(value, t1, prime);
}

inline bool BigNumber::operator==(mpz_t &source)
{
    return (mpz_cmp(value, source) == 0);
}

inline bool BigNumber::operator==(unsigned long long &sourceInteger)
{
    return (mpz_cmp_ui(value, sourceInteger) == 0);
}

inline bool BigNumber::operator<(mpz_t &source)
{
    return (mpz_cmp(value, source) < 0);
}

inline bool BigNumber::operator<(unsigned long long &sourceInteger)
{
    return (mpz_cmp_ui(value, sourceInteger) < 0);
}

inline bool BigNumber::operator>(mpz_t &source)
{
    return (mpz_cmp(value, source) > 0);
}

inline bool BigNumber::operator>(unsigned long long &sourceInteger)
{
    return (mpz_cmp_ui(value, sourceInteger) > 0);
}

inline void BigNumber::operator^=(mpz_t &power)
{
    mpz_powm(value, value, power, prime);
}

inline void BigNumber::operator^=(char *powerString)
{   
    mpz_set_str(t1, powerString, PREFFERED_BASE);
    mpz_powm(value, value, t1, prime);
}

inline void BigNumber::operator^=(unsigned long long &powerInteger)
{
    mpz_powm_ui(value, value, powerInteger, prime);
}

inline mpz_t& BigNumber::getValuePointer()
{
    return value;
}

void printConstants()
{
    gmp_printf("\nPrime: %Zx \nOrder: %Zx", prime, order);
}

void neg(mpz_t &result, mpz_t &number){
    mpz_sub(result, prime, number);
}

void add(mpz_t &result, mpz_t &A, mpz_t &B)
{
    mpz_add(t1, A, B);
    mpz_mmod(result, t1, prime);
}

void sub(mpz_t &result, mpz_t &A, mpz_t &B)
{
    neg(t1, B);
    add(result, A, t1);
}

void mul(mpz_t &result, mpz_t &number, mpz_t &multiple)
{
    mpz_mul(t1, number, multiple);
    mpz_mmod(result, t1, prime);
}

void div(mpz_t &result, mpz_t &number, mpz_t &divisor)
{
    mpz_invert(t1, divisor, prime);
    mpz_mul(t2, number, t1);
    mpz_mmod(result, t2, prime);
}

void pow(mpz_t &result, mpz_t &number, mpz_t &power){
    mpz_powm(result, number, power, prime);
}

void addKeys(mpz_t &result, mpz_t &key1, mpz_t &key2)
{
    mpz_add(t1, key1, key2);
    mpz_mmod(result, t1, order);
}

void modSqrt(mpz_t &result, mpz_t &number)
{
    ///Tonelli–Shanks algorithm - since the prime always results in s = 1, only one branch of the algorithm is needed
    pow(t1, number, primePlusOneDivFour);
    pow(t2, t1, two);
    if(mpz_cmp(t2, number) == 0)
    {
       mpz_set(result, t1);
    }
    else
    {
       mpz_set(result, zero);
    }
}

void generateRandomKey(mpz_t &result)
{
    gmp_randseed_ui(randomState, random());
    mpz_urandomb(result, randomState, 250u);
}