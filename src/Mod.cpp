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

    // //// Cipolla algorithm - work in progress, do not use
    // void modSqrt(mpz_t &result, mpz_t &number, mpz_t &primeModulo)
    // {
    //     typedef struct fp2
    //     {
    //         private:
    //             mpz_t x, y;
    //         public:
    //             fp2()
    //             {
    //                 mpz_init(x);
    //                 mpz_init(y);
    //             }
    //             fp2(mpz_t &init_x, mpz_t &init_y)
    //             {
    //                 mpz_init_set(x, init_x);
    //                 mpz_init_set(y, init_y);
    //             }
    //             fp2(unsigned long long &init_x, unsigned long long &init_y)
    //             {
    //                 mpz_init_set_ui(x, init_x);
    //                 mpz_init_set_ui(y, init_y);
    //             }
    //             void operator = (fp2 n)
    //             {
    //                 mpz_set(x, n.x);
    //                 mpz_set(y, n.y);
    //             }
    //             void fp2mul(fp2 result, fp2 a, fp2 b, mpz_t p, mpz_t w2)
    //             {
    //                 mul_mod(t1, a.x, b.x, p);
    //                 mul_mod(t2, a.y, b.y, p);
    //                 mul_mod(t2, t2, w2, p);
    //                 add_mod(result.x, t1, t2, prime);
    //                 mul_mod(t1, a.x, b.y, prime);
    //                 mul_mod(t2, a.y, b.x, prime);
    //                 mul_mod(result.y, t1, t2, prime);
    //                 ///Function complexity: 7*(mod) + 6*(mul) + 1*(add)
    //             }
    //             void fp2square(fp2 &result, fp2 &a, mpz_t &prime, mpz_t &w2)
    //             {
    //                 fp2mul(result, a, a, prime, w2);
    //             }

    //             void fp2pow(fp2 &result, fp2 &a, mpz_t &number, mpz_t &p, mpz_t &w2)
    //             {
    //                 mpz_t n;
    //                 mpz_init_set(n, number);
    //                 int nZero_or_One = (mpz_cmp_ui(n, 1));

    //                 switch(nZero_or_One)
    //                 {
    //                     case 0: /// n == 1
    //                         break;
    //                     case -1: /// n < 1
    //                         mpz_set_ui(result.x, 1);
    //                         mpz_set_ui(result.y, 0);
    //                         break;
    //                     case 1:
    //                         if (mpz_even_p(n))
    //                         {
    //                             mpz_div_2exp(n, n, 1);
    //                             fp2pow(result, a, n, p, w2);
    //                             fp2square(result, a, p, w2);
    //                         }
    //                         else
    //                         {
    //                             mpz_sub_ui(n, n, 1u);
    //                             fp2pow(result, a, n, p, w2);
    //                             fp2mul(result, a, result, p, w2);
    //                         }
    //                         break;
    //                 }
    //                 ///Function Complexity: Iterations*( 1*(sub) + 1(pow) + 1(mul)
    //             }

    //     };
    // }
    // uint64_t randULong(uint64_t min, uint64_t max)
    // {
    //     uint64_t t = (uint64_t)rand();
    //     return min + t % (max - min);
    // }

    // returns a * b mod modulus
    // uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t modulus)
    // {
    //     uint64_t x = 0, y = a % modulus;

    //     while (b > 0)
    //     {
    //         if ((b & 1) == 1)
    //         {
    //             x = (x + y) % modulus;
    //         }
    //         y = (y << 1) % modulus;
    //         b = b >> 1;
    //     }
    //     return x;
    // }

    // returns b ^^ power mod modulus
    // uint64_t pow_mod(uint64_t b, uint64_t power, uint64_t modulus)
    // {
    //     uint64_t x = 1;

    //     while (power > 0)
    //     {
    //         if ((power & 1) == 1)
    //         {
    //             x = mul_mod(x, b, modulus);
    //         }
    //         b = mul_mod(b, b, modulus);
    //         power = power >> 1;
    //     }

    //     return x;
    // }

    // // miller-rabin prime test
    // bool isPrime(uint64_t n, int64_t k)
    // {
    //     uint64_t a, x, n_one = n - 1, d = n_one;
    //     uint32_t s = 0;
    //     uint32_t r;

    //     if (n < 2)
    //     {
    //         return false;
    //     }

    //     // limit 2^63, pow_mod/mul_mod can't handle bigger numbers
    //     if (n > 9223372036854775808ull)
    //     {
    //         printf("The number is too big, program will end.\n");
    //         exit(1);
    //     }

    //     if ((n % 2) == 0)
    //     {
    //         return n == 2;
    //     }

    //     while ((d & 1) == 0)
    //     {
    //         d = d >> 1;
    //         s = s + 1;
    //     }

    //     while (k > 0)
    //     {
    //         k = k - 1;
    //         a = randULong(2, n);
    //         x = pow_mod(a, d, n);
    //         if (x == 1 || x == n_one)
    //         {
    //             continue;
    //         }
    //         for (r = 1; r < s; r++)
    //         {
    //             x = pow_mod(x, 2, n);
    //             if (x == 1)
    //                 return false;
    //             if (x == n_one)
    //                 goto continue_while;
    //         }
    //         if (x != n_one)
    //         {
    //             return false;
    //         }

    //     continue_while:
    //     {
    //     }
    //     }

    //     return true;
    // }

    ///////mpz_probab_prime_p();

    // int64_t legendre_symbol(int64_t a, int64_t p)
    // {
    //     int64_t x = pow_mod(a, (p - 1) / 2, p);
    //     if ((p - 1) == x)
    //     {
    //         return x - p;
    //     }
    //     else
    //     {
    //         return x;
    //     }
    // }
    ////////mpz_legendre();

    // fp2 fp2mul(struct fp2 a, struct fp2 b, int64_t p, int64_t w2)
    // {
    //     struct fp2 answer;
    //     uint64_t tmp1, tmp2;

    //     tmp1 = mul_mod(a.x, b.x, p);
    //     tmp2 = mul_mod(a.y, b.y, p);
    //     tmp2 = mul_mod(tmp2, w2, p);
    //     answer.x = (tmp1 + tmp2) % p;
    //     tmp1 = mul_mod(a.x, b.y, p);
    //     tmp2 = mul_mod(a.y, b.x, p);
    //     answer.y = (tmp1 + tmp2) % p;

    //     return answer;
    // }

    // struct fp2 fp2square(struct fp2 a, int64_t p, int64_t w2)
    // {
    //     return fp2mul(a, a, p, w2);
    // }

    //     void test(mpz_t &n, mpz_t &p)
    //     {
    //         mpz_t a, w2;
    //         mpz_t x1, x2;
    //         fp2 answer;

    //         gmp_printf("Find solution for n = %Zd and p = %Zd\n", n, p);
    //         // if (p == 2 || !isPrime(p, 15))
    //         if( (mpz_cmp_ui(p, 2) == 0) || mpz_probab_prime_p(p)
    //         {
    //             printf("No solution, p is not an odd prime.\n\n");
    //             return;
    //         }

    //         // p is checked and is a odd prime
    //         // if (legendre_symbol(n, p) != 1)
    //         if(mpz_legendre(n, p) != 1)
    //         {
    //             gmp_printf(" %Zd is not a square in F%Zd\n\n", n, p);
    //             return;
    //         }
    //         mpz_sub(t1, p, two); /// cover the random range issue without checking the result for numbers smaller than 3
    //         mpz_set_str(t1, primePlusOneDivTwo_String);
    //         while (true)
    //         {
    //             do
    //             {
    //                 ///generate a random number in the range (2, prime)
    //                 mpz_urandomm(a, randomState, t1); ///TODO: see if it is possible to use a pre generated set of high entropy numbers (as compared to numbers of trials neccessary for determining primality of a known number set)
    //                 mpz_add(a, a, two);

    //                 mpz_mul(w2, a, a);
    //                 mpz_sub(w2, w2, n);
    //             }
    //             while (mpz_legendre(w2, p) != 1);

    //             mpz_set(answer.x, a);
    //             mpz_set_ui(answer.y, 1);

    //             fp2pow(answer, answer, t1, p, w2);
    //             if (answer.y != 0)
    //             {
    //                 continue;
    //             }

    //             x1 = answer.x;
    //             x2 = p - x1;
    //             if (mul_mod(x1, x1, p) == n && mul_mod(x2, x2, p) == n)
    //             {
    //                 printf("Solution found: x1 = %lld, x2 = %lld\n\n", x1, x2);
    //                 return;
    //             }
    //         }
    //     }
    // };

    // void mpz_modSqrt(mpz_t &number, mpz_t &prime)
    // {
    //     if (mpz_legendre(number, prime) != 1)
    //     {
    //         gmp_printf(" %Zd is not a square in F%Zd\n\n", number, prime);
    //         return;
    //     }

    //     mpz_t a, w2, e;
    //     mpz_inits(a, w2, e);
    //     while (mpz_legendre(number, prime) != 1)
    //     {
    //         mpz_add_ui(a, a, 1)
    //         mpz_mul(w2, a, a);
    //         mpz_sub(w2, w2, &number);
    //         mpz_mod(w2, w2, prime);
    //     }

    //     fp2 r(1, 0), s(a, one);

    //     while(1)
    //     {
    //         mpz_add(e, prime, one);
    //         mpz_probab_prime_p(e, PRIME_TRIALS);
    //     }
    // }