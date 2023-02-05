#include "Point.h"

/* Local Includes */
#include "../../Utility/GlobalData/ErrorCodes.h"
#include "../../Utility/GlobalData/Definitions.h"
#include "../ModularArithmetic/Mod.h"
#include <cstring>
#include <math.h>

/*
    Point.cpp
    Contains point arithmetic functionality using modulo operations over the prime integer field
    Wrapper functions are provided for ease of use
    Overloaded operators are provided as wrappers for ease of use. Do ~NOT~ use for critical functionality
*/

unsigned long long returnValue = 0u;

extern mpz_t moduloHalb;
extern mpz_t order;
extern mpz_t one;
extern mpz_t two;
extern mpz_t three;
extern mpz_t four;
extern mpz_t five;
extern mpz_t six;
extern mpz_t seven;
extern mpz_t order;
extern mpz_t prime;

Point localTempPoint1;
Point localTempPoint2;

Point GeneratorPoints[255];

unsigned int init_Point()
{

    if (strcmp(localTempPoint1.getK(), kG0_String) != 0)
    {
        return POINT_E_INITIALIZATION_K_INVALID;
    }

    if (strcmp(localTempPoint1.getX(), xG0_String) != 0)
    {
        return POINT_E_INITIALIZATION_X_INVALID;
    }

    if (strcmp(localTempPoint1.getY(), yG0_String) != 0)
    {
        return POINT_E_INITIALIZATION_Y_INVALID;
    }

    localTempPoint1*=(two);

    if (strcmp(localTempPoint1.getK(), kG1_String) != 0)
    {
        return POINT_E_ADDITION_K_INVALID;
    }

    if (strcmp(localTempPoint1.getX(), xG1_String) != 0)
    {
        return POINT_E_ADDITION_X_INVALID;
    }

    if (strcmp(localTempPoint1.getY(), yG1_String) != 0)
    {
        return POINT_E_ADDITION_Y_INVALID;
    }

    localTempPoint1 += localTempPoint2;
    localTempPoint1 += localTempPoint2;

    if (strcmp(localTempPoint1.getK(), kG2_String) != 0)
    {
        return POINT_E_ADDITION_K_INVALID;
    }

    if (strcmp(localTempPoint1.getX(), xG2_String) != 0)
    {
        return POINT_E_ADDITION_X_INVALID;
    }

    if (strcmp(localTempPoint1.getY(), yG2_String) != 0)
    {
        return POINT_E_ADDITION_Y_INVALID;
    }

    localTempPoint1 = (char *)(kG2_String);

    localTempPoint2 = (char *)(kG1_String);

#ifdef POINTDEBUG
    printf("tempInitialPointK: %s\n",   localTempPoint1.getK());
    printf("tempInitialPointX: %s\n",   localTempPoint1.getX());
    printf("tempInitialPointY: %s\n\n", localTempPoint1.getY());

    printf("tempSubtractedPointK: %s\n",   localTempPoint2.getK());
    printf("tempSubtractedPointX: %s\n",   localTempPoint2.getX());
    printf("tempSubtractedPointY: %s\n\n", localTempPoint2.getY());
#endif

    localTempPoint1 -= localTempPoint2;
        // localTempPoint1.subPoint(localTempPoint1, localTempPoint2);

#ifdef POINTDEBUG
    printf("tempResultPointK: %s\n", localTempPoint1.getK());
    printf("tempResultPointX: %s\n",   localTempPoint1.getX());
    printf("tempResultPointY: %s\n\n", localTempPoint1.getY());
#endif

    if (strcmp(localTempPoint1.getK(), kG1_String) != 0)
    {
        return POINT_E_SUBTRACTION_K_INVALID;
    }

    if (strcmp(localTempPoint1.getX(), xG1_String) != 0)
    {
        return POINT_E_SUBTRACTION_X_INVALID;
    }

    if (strcmp(localTempPoint1.getY(), yG1_String) != 0)
    {
        return POINT_E_SUBTRACTION_Y_INVALID;
    }

    printf("Point OK\n");

    return POINT_E_OK;
}

///Affine (cartesian) points
Point::Point()
{
    mpz_init_set_str(this->k, kG0_String, PREFFERED_BASE);
    mpz_init_set_str(this->x, xG0_String, PREFFERED_BASE);
    mpz_init_set_str(this->y, yG0_String, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    // mpz_inits(t1, t2, m, n); - the m and n variables are required to be 1 for the calculations to work
}

Point::Point(Point &source)
{
    mpz_init_set_str(this->k, source.getK(), PREFFERED_BASE);
    mpz_init_set_str(this->x, source.getX(), PREFFERED_BASE);
    mpz_init_set_str(this->y, source.getY(), PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
}

Point::Point(mpz_t &key)
{
    mpz_init_set_str(this->x, xG0_String, PREFFERED_BASE);
    mpz_init_set_str(this->y, yG0_String, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_ui(k, 1);
    this->multiplyByFactor(*this, key);
}

Point::Point(const char xString[], const char yString[]) {
    mpz_init_set_str(this->x, xString, PREFFERED_BASE);
    mpz_init_set_str(this->y, yString, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_ui(k, 0);
}

Point::Point(const char *xString, const char *yString, const char *kString) {
    mpz_init_set_str(this->x, xString, PREFFERED_BASE);
    mpz_init_set_str(this->y, yString, PREFFERED_BASE);
    mpz_init_set_ui(t1, 0);
    mpz_init_set_ui(t2, 0);
    mpz_init_set_ui(m, 1);
    mpz_init_set_ui(n, 1);
    mpz_init_set_str(k, kString, PREFFERED_BASE);
    keyKnown = true;
}

Point::~Point()
{
    mpz_clear(this->x);
    mpz_clear(this->y);
    mpz_clear(this->k);
    mpz_clear(this->t1);
    mpz_clear(this->t2);
    mpz_clear(this->m);
    mpz_clear(this->n);
}


void Point::operator=(Point &source)
{
    mpz_set(this->x, source.x);
    mpz_set(this->y, source.y);
    mpz_set(this->k, source.k);
    this->keyKnown = source.keyKnown;
}

void Point::operator=(mpz_t &key)
{
    this->reset();
    this->multiplyByFactor(*this, key);
}

void Point::operator=(char *keyString)
{
    mpz_set_str(t1, keyString, PREFFERED_BASE);
    this->reset();
    this->multiplyByFactor(*this, t1);
}

Point& Point::operator-=(Point &source)
{
#ifdef POINTDEBUG
    gmp_printf("subtractantPointK: %s\n",   this->getK());
    gmp_printf("subtractantPointX: %s\n",   this->getX());
    gmp_printf("subtractantPointY: %s\n\n", this->getY());

    gmp_printf("subtractedPointK: %s\n",   source.getK());
    gmp_printf("subtractedPointX: %s\n",   source.getX());
    gmp_printf("subtractedPointY: %s\n\n", source.getY());
#endif

    this->negate();

#ifdef POINTDEBUG
    gmp_printf("negatedPointK: %s\n",   this->getK());
    gmp_printf("negatedPointX: %s\n",   this->getX());
    gmp_printf("negatedPointY: %s\n\n", this->getY());
#endif

    *this += source;
    
    this->negate();

    return *this;
}

Point &Point::operator+=(Point &source)
{
    /// TODO:  test to see if it's consistent with the addPoint function
    mpz_add(t1, source.k, this->k);
    mpz_mmod(this->k, t1, order);

    sub(t1, source.y, this->y);     /// t1 = By - Ay mod p
    sub(t2, source.x, this->x);     /// t2 = Bx - Ax mod p
    div(m, t1, t2);                 /// m  = t1 / t2 mod p
    mul(t1, m, this->x);            /// t1 = m * Ax mod p
    sub(n, this->y, t1);            /// n = Ax - t1 mod p
    pow(t1, m, two);                /// t1 = m * m
    sub(t2, t1, this->x);           /// t2 = t1 - Ax
    sub(this->x, t2, source.x);     /// Cx = t2 - Bx
    mul(t1, m, this->x);            /// t1 = m * Cx
    add(t2, t1, n);                 /// t2 = t1 + n
    neg(this->y, t2);               /// Cy = neg(t2)
    return *this;
}

Point& Point::operator*=(unsigned long long factor)
{
    ///TODO: Check if operator matches multiplyByFactor and multiplyBy2 functions
    if (factor > 0)
    {
        if(factor > 2u)
        {
            this->multiplyByFactor(*this, factor);
        }
        else
        {
            this->multiplyBy2(*this);
        }
    }
    return *this;
    /// factor ^ 1 leaves the number unchanged   
}

Point& Point::operator*=(mpz_t &factor)
{
    ///TODO: Check if operator matches multiplyByFactor and multiplyBy2 functions
    returnValue = mpz_cmp_ui(factor, 1u);
    if(returnValue < 0)
        this->reset();
    else 
    if (returnValue > 0)
    {
        if(mpz_cmp_ui(factor, 2u) > 0)
        {
            this->multiplyByFactor(*this, factor);
        }
        else
        {
            this->multiplyBy2(*this);
        }
    }
    return *this;
    /// factor ^ 1 leaves the number unchanged   
}

Point& Point::operator/= (mpz_t &factor)
{
    mpz_t invertedFactor;
    mpz_init(invertedFactor);
    mpz_invert (invertedFactor, factor, order);
    *this *= invertedFactor;
    return *this;
}

Point& Point::operator/= (unsigned long long intFactor)
{
    mpz_t invertedFactor;
    mpz_t trueFactor;
    mpz_init(invertedFactor);
    mpz_init_set_ui(trueFactor, intFactor);
    mpz_invert (invertedFactor, trueFactor, order);
    *this *= invertedFactor;
    return *this;
}

bool Point::operator==(Point &source)
{
    return (
            (mpz_cmp(this->x, source.x) == 0) &&
            (mpz_cmp(this->y, source.y) == 0)
           );
}

bool Point::operator!=(Point &source)
{
    return !(*this == source);
}

void Point::negate() 
{
    mpz_sub(this->k, order, this->k);
    mpz_sub(this->y, prime, this->y);
}

void Point::addPoint(Point &result, Point &B)
{
//    m         = div( sub(yP2, yP1) , sub(xP2,xP1) );
//    n         = sub(yP1 , mul(m,xP1));
//    result.x  = sub(sub(mul(m,m) ,(xP1)) , (xP2));
//    result.y  = neg(add(mul(m,result.x) , n));

mpz_add(t1, this->k, B.k);
mpz_mmod(result.k, t1, order);

sub(t1, B.y, this->y);  /// t1  = By - Ay mod p
sub(t2, B.x, this->x);  /// t2  = Bx - Ax mod p
div(m, t1, t2);         /// m   = t1 / t2 mod p
mul(t1, m, this->x);    /// t1  = m * Ax mod p
sub(n, this->y, t1);    /// n   = Ax - t1 mod p
pow(t1, m, two);        /// t1  = m * m
sub(t2, t1, this->x);   /// t2  = t1 - Ax
sub(result.x, t2, B.x); /// Cx  = t2 - Bx
mul(t1, m, result.x);   /// t1  = m * Cx
add(t2, t1, n);         /// t2  = t1 + n
neg(result.y, t2);      /// Cy  = neg(t2)
}

void Point::subPoint(Point &result, Point &B)
{
    B.negate();
    mpz_add(t1, this->k, B.k);
    mpz_mmod(result.k, t1, order);

    sub(t1, B.y, this->y);  /// t1  = By - Ay mod p
    sub(t2, B.x, this->x);  /// t2  = Bx - Ax mod p
    div(m, t1, t2);         /// m   = t1 / t2 mod p
    mul(t1, m, this->x);    /// t1  = m * Ax mod p
    sub(n, this->y, t1);    /// n   = Ax - t1 mod p
    pow(t1, m, two);        /// t1  = m * m
    sub(t2, t1, this->x);   /// t2  = t1 - Ax
    sub(result.x, t2, B.x); /// Cx  = t2 - Bx
    mul(t1, m, result.x);   /// t1  = m * Cx
    add(t2, t1, n);         /// t2  = t1 + n
    neg(result.y, t2);      /// Cy  = neg(t2)

    B.negate();
}

void Point::multiplyBy2(Point &result)
{
    mpz_mul_ui(t1, this->k, 2);
    mpz_mmod(result.k, t1, order);

    //	m = (3 * X²) / (2 * sqrt(X²+7))
    //	n = Y - m * X;
    //	result.x = m² - 2*X
    //	result.y = -(m*result.x + n)
    // -------------------- //
    pow     (m, x, two);        // m        = x^2)
    mul     (t1, three, m);     // t1       = 3 * x^2
    pow     (m, x, three);      // m        = x^3
    add     (t2, m, seven);     // t2       = x^3 + 7
    modSqrt (m, t2);            // m        = sqrt(x^3 + 7)
    mul     (t2, m, two);       // t2       = 2 * sqrt(x^3 + 7)
    mul     (t2, y, two);       // t2       = 2 * y
    div     (m, t1, t2);        // m        = (3 * x^2) / (2 * sqrt(x^3 + 7));
    mul     (t1, m, x);         // t1       = x * (3 * x^2) / (2 * sqrt(x^3 + 7))
    sub     (n, y, t1);         // n        = y - (x * (3 * x^2) / (2 * sqrt(x^3 + 7)))
    mul     (t1, x, two);       // t1       = 2 * x
    pow     (t2, m, two);       // t2       = ((3 * x^2) / (2 * sqrt(x^3 + 7))) ^ 2
    sub     (result.x, t2, t1); // result.x = ((3 * x^2) / (2 * sqrt(x^3 + 7))) ^ 2 - 2 * x
    mul     (t1, m, result.x);  // t1       = (3 * x^2) / (2 * sqrt(x^3 + 7)) * result.x
    add     (t2, t1, n);        // t2       = (3 * x^2) / (2 * sqrt(x^3 + 7)) * result.x + n
    neg     (result.y, t2);     // result.y = -((3 * x^2) / (2 * sqrt(x^3 + 7)) * result.x + n)
}

void Point::multiplyByFactor(Point &result, mpz_t &factor)
{
    unsigned long factorSize = mpz_sizeinbase(factor, 2);
    Point temp(*this);

    unsigned long i = 0;

    while (mpz_tstbit(factor, i) == 0) /// covers the case when factor's LSB is not 0
    {
        temp.multiplyBy2(temp);
        ++i;
    }
    result = temp;
    
    ++i;
    for (i; i < factorSize; ++i)
    {
        temp.multiplyBy2(temp);
        if (mpz_tstbit(factor, i))
        {
            result += temp;
        }
    }
}

void Point::divideByFactor(Point &result, mpz_t &factor)
{
    mpz_t invFactor;
    mpz_init(invFactor);
    mpz_invert(invFactor, factor, order);
    this->multiplyByFactor(result, invFactor);
}

void Point::multiplyByFactor(Point &result, unsigned long long &factor)
{
    unsigned int factorSize = log2(factor);
    Point temp(*this);
    unsigned long long i = 0b1;
    unsigned int j = 0u;

    while (factor ^ i) /// covers the case when factor's LSB is not 0
    {
        temp.multiplyBy2(temp);
        i <<= 1;
        j++;
    }
    result = temp;
    i <<= 1;
    ++j;
    for (;j < factorSize; ++j) //by left-shitfing i outside the allowed register, a value of 0 is obtained
    {
        temp.multiplyBy2(temp);
        if (factor & i)
        {
            result += temp;
        }
    }
}

char *Point::getK() 
{
    return mpz_get_str(NULL, PREFFERED_BASE, this->k);
}

char *Point::getX()
{
    return mpz_get_str(NULL, PREFFERED_BASE, this->x);
}

char *Point::getY()
{
    return mpz_get_str(NULL, PREFFERED_BASE, this->y);
}

LSB_HASH_TYPE Point::getLSB()
{
    return x->_mp_d[0];
}

void Point::setK(const char *kValue, int base, bool known)
{
    mpz_set_str(k, kValue, base);
    keyKnown = known;
}

void Point::setX(const char *xCoordinate, int base)
{
    mpz_set_str(x, xCoordinate, base);
}

void Point::setY(const char *yCoordinate, int base)
{
    mpz_set_str(y, yCoordinate, base);
}

void Point::reset()
{
    mpz_set_ui (this->k, 1);
    mpz_set_str(this->x, xG0_String, PREFFERED_BASE);
    mpz_set_str(this->y, yG0_String, PREFFERED_BASE);
}

void Point::printPointInfo()
{

    // gmp_printf("K: %Zx\n",    k);
    gmp_printf("X: %Zx\n",    x);
    gmp_printf("Y: %Zx\n\n",    y);
    if(keyKnown)
    {
        gmp_printf("key unknown\n");
    }
}

void Point::printDec()
{
    gmp_printf("\n x: %Zd", x);
    gmp_printf("\n y: %Zd", y);
    gmp_printf("\n");
}

void Point::printHex()
{
    gmp_printf("\n x: %Zx", x);
    gmp_printf("\n y: %Zx", y);
    if (keyKnown)
    {
        gmp_printf("\n K: %Zx", k);
    }
    else
    {
        gmp_printf("\n K +: %Zx", k);
    }
    gmp_printf("\n");
}

bool Point::checkY() 
{
    pow(t1, y, two);
    pow(t2, x, three);
    add(t2, t2, seven);
    if(mpz_cmp(t1, t2) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char *Point::generateY()
{
    pow(t1, x, three);                 // X^3
    add(t2, t1, seven);                // X^3 + 7
    modSqrt(t1, t2);                   // sqrt(X^3 + 7)
    mpz_get_str(outputString, PREFFERED_BASE, t1); // output Y
    neg(t2, t1);
    mpz_get_str(outputString, PREFFERED_BASE, t2); // output -Y
    return outputString;
}

bool Point::isKeyKnown()
{
    return this->keyKnown;
}

///Tester functions

void Point::toggleKeyKnowledgeState()
{
    this->keyKnown = !keyKnown;
}

///Jacoby (cartesian) points

///TODO: Implement Jacoby type operations for accelerated point multiplication