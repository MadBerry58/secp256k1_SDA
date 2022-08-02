/*
    Point.cpp
    Contains point arithmetic functionality using modulo operations over the prime integer field
    Wrapper functions are provided for ease of use
    Overloaded operators are provided as wrappers for ease of use. Do ~NOT~ use for critical functionality
*/
#ifndef SECP256K1_SANDBOX_POINT_CPP
#define SECP256K1_SANDBOX_POINT_CPP
#include "Point.h"

#include "../ModularArithmetic/Mod.h"

// #define POINTDEBUG

unsigned int returnValue = 0u;

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

unsigned int pointInit()
{
    DEBUG_MSG("%s\n", localTempPoint1.getK());

    if (strcmp(localTempPoint1.getK(), kG0_String) != 0)
    {
        DEBUG_MSG("Point key assignment failed \n");
        return POINT_E_INITIALIZATION_K_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getX());
    if (strcmp(localTempPoint1.getX(), xG0_String) != 0)
    {
        DEBUG_MSG("Point X assignment failed \n");
        return POINT_E_INITIALIZATION_X_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getY());
    if (strcmp(localTempPoint1.getY(), yG0_String) != 0)
    {
        DEBUG_MSG("Point Y key assignment failed\n");
        return POINT_E_INITIALIZATION_Y_INVALID;
    }

    localTempPoint1*=(two);

    DEBUG_MSG("%s\n", localTempPoint1.getK());
    if (strcmp(localTempPoint1.getK(), kG1_String) != 0)
    {
        DEBUG_MSG("Point multiplication by 2 key assignment failed\n");
        return POINT_E_ADDITION_K_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getX());

    if (strcmp(localTempPoint1.getX(), xG1_String) != 0)
    {
        DEBUG_MSG("Point multiplication by 2 X assignment failed\n");
        return POINT_E_ADDITION_X_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getY());

    if (strcmp(localTempPoint1.getY(), yG1_String) != 0)
    {
        DEBUG_MSG("Point multiplication by 2 Y assignment failed\n");
        return POINT_E_ADDITION_Y_INVALID;
    }

    localTempPoint1 += localTempPoint2;
    localTempPoint1 += localTempPoint2;

    DEBUG_MSG("%s\n", localTempPoint1.getK());
    if (strcmp(localTempPoint1.getK(), kG2_String) != 0)
    {
        DEBUG_MSG("Point addition key assignment failed\n");
        return POINT_E_ADDITION_K_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getX());
    if (strcmp(localTempPoint1.getX(), xG2_String) != 0)
    {
        DEBUG_MSG("Point addition X assignment failed\n");
        return POINT_E_ADDITION_X_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getY());

    if (strcmp(localTempPoint1.getY(), yG2_String) != 0)
    {
        DEBUG_MSG("Point addition Y assignment failed\n");
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

    DEBUG_MSG("%s\n", localTempPoint1.getK());
    if (strcmp(localTempPoint1.getK(), kG1_String) != 0)
    {
        DEBUG_MSG("Point subtraction key assignment failed\n");
        return POINT_E_SUBTRACTION_K_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getX());

    if (strcmp(localTempPoint1.getX(), xG1_String) != 0)
    {
        DEBUG_MSG("Point subtraction X assignment failed\n");
        return POINT_E_SUBTRACTION_X_INVALID;
    }

    DEBUG_MSG("%s\n", localTempPoint1.getY());

    if (strcmp(localTempPoint1.getY(), yG1_String) != 0)
    {
        DEBUG_MSG("Point subtraction Y assignment failed\n");
        return POINT_E_SUBTRACTION_Y_INVALID;
    }
    generatorConstantsInit();

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
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(t1);
    mpz_clear(t2);
    mpz_clear(m);
    mpz_clear(n);
    mpz_clear(k);
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

void Point::operator*=(mpz_t &factor)
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
    /// factor ^ 1 leaves the number unchanged   
}

void Point::operator/= (mpz_t &factor)
{
    returnValue = mpz_cmp_ui(factor, 1u);
    if  (returnValue < 0)
        this->reset();
    else if
        (returnValue > 0)
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
}

bool Point::operator==(Point &source)
{
    return (
              (mpz_cmp(this->k, source.k) == 0)
            &&(mpz_cmp(this->x, source.x) == 0)
            &&(mpz_cmp(this->y, source.y) == 0)
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

    gmp_printf("K: %Zx\n",    k);
    gmp_printf("X: %Zx\n",    x);
    gmp_printf("Y: %Zx\n",      y);
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
    DEBUG_MSG("Y: %Zx\n", t1);
    neg(t2, t1);
    mpz_get_str(outputString, PREFFERED_BASE, t2); // output -Y
    DEBUG_MSG("-Y: %Zx\n", t2);
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

int generatorConstantsInit()
{
    std::map<int, std::string> kGs;
    std::map<int, std::string> xGs;
    std::map<int, std::string> yGs;

    kGs.insert(std::pair<int, std::string>(0, " 1"));
    xGs.insert(std::pair<int, std::string>(0, " 79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"));
    yGs.insert(std::pair<int, std::string>(0, " 483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"));

    kGs.insert(std::pair<int, std::string>(1, " 0"));
    xGs.insert(std::pair<int, std::string>(1, " c6047f9441ed7d6d3045406e95c07cd85c778e4b8cef3ca7abac09b95c709ee5"));
    yGs.insert(std::pair<int, std::string>(1, " 1ae168fea63dc339a3c58419466ceaeef7f632653266d0e1236431a950cfe52a"));

    kGs.insert(std::pair<int, std::string>(2, " 0"));
    xGs.insert(std::pair<int, std::string>(2, " e493dbf1c10d80f3581e4904930b1404cc6c13900ee0758474fa94abe8c4cd13"));
    yGs.insert(std::pair<int, std::string>(2, " 51ed993ea0d455b75642e2098ea51448d967ae33bfbdfe40cfe97bdc47739922"));

    kGs.insert(std::pair<int, std::string>(3, " 0"));
    xGs.insert(std::pair<int, std::string>(3, " 2f01e5e15cca351daff3843fb70f3c2f0a1bdd05e5af888a67784ef3e10a2a01"));
    yGs.insert(std::pair<int, std::string>(3, " 5c4da8a741539949293d082a132d13b4c2e213d6ba5b7617b5da2cb76cbde904"));

    kGs.insert(std::pair<int, std::string>(4, " 0"));
    xGs.insert(std::pair<int, std::string>(4, " e60fce93b59e9ec53011aabc21c23e97b2a31369b87a5ae9c44ee89e2a6dec0a"));
    yGs.insert(std::pair<int, std::string>(4, " f7e3507399e595929db99f34f57937101296891e44d23f0be1f32cce69616821"));

    kGs.insert(std::pair<int, std::string>(5, " 0"));
    xGs.insert(std::pair<int, std::string>(5, " d30199d74fb5a22d47b6e054e2f378cedacffcb89904a61d75d0dbd407143e65"));
    yGs.insert(std::pair<int, std::string>(5, " 95038d9d0ae3d5c3b3d6dec9e98380651f760cc364ed819605b3ff1f24106ab9"));

    kGs.insert(std::pair<int, std::string>(6, " 0"));
    xGs.insert(std::pair<int, std::string>(6, " bf23c1542d16eab70b1051eaf832823cfc4c6f1dcdbafd81e37918e6f874ef8b"));
    yGs.insert(std::pair<int, std::string>(6, " 5cb3866fc33003737ad928a0ba5392e4c522fc54811e2f784dc37efe66831d9f"));

    kGs.insert(std::pair<int, std::string>(7, " 0"));
    xGs.insert(std::pair<int, std::string>(7, " 34ff3be4033f7a06696c3d09f7d1671cbcf55cd700535655647077456769a24e"));
    yGs.insert(std::pair<int, std::string>(7, " 5d9d11623a236c553f6619d89832098c55df16c3e8f8b6818491067a73cc2f1a"));

    kGs.insert(std::pair<int, std::string>(8, " 0"));
    xGs.insert(std::pair<int, std::string>(8, " 8282263212c609d9ea2a6e3e172de238d8c39cabd5ac1ca10646e23fd5f51508"));
    yGs.insert(std::pair<int, std::string>(8, " 11f8a8098557dfe45e8256e830b60ace62d613ac2f7b17bed31b6eaff6e26caf"));

    kGs.insert(std::pair<int, std::string>(9, " 0"));
    xGs.insert(std::pair<int, std::string>(9, " 465370b287a79ff3905a857a9cf918d50adbc968d9e159d0926e2c00ef34a24d"));
    yGs.insert(std::pair<int, std::string>(9, " 35e531b38368c082a4af8bdafdeec2c1588e09b215d37a10a2f8fb20b33887f4"));

    kGs.insert(std::pair<int, std::string>(10, " 0"));
    xGs.insert(std::pair<int, std::string>(10, " 241febb8e23cbd77d664a18f66ad6240aaec6ecdc813b088d5b901b2e285131f"));
    yGs.insert(std::pair<int, std::string>(10, " 513378d9ff94f8d3d6c420bd13981df8cd50fd0fbd0cb5afabb3e66f2750026d"));

    kGs.insert(std::pair<int, std::string>(11, " 0"));
    xGs.insert(std::pair<int, std::string>(11, " 5d1bdb4ea172fa79fce4cc2983d8f8d9fc318b85f423de0dedcb63069b920471"));
    yGs.insert(std::pair<int, std::string>(11, " 2843826779379e2e794bb99438a2265679eb1e9996c56e7b70330666f7b83103"));

    kGs.insert(std::pair<int, std::string>(12, " 0"));
    xGs.insert(std::pair<int, std::string>(12, " 175e159f728b865a72f99cc6c6fc846de0b93833fd2222ed73fce5b551e5b739"));
    yGs.insert(std::pair<int, std::string>(12, " d3506e0d9e3c79eba4ef97a51ff71f5eacb5955add24345c6efa6ffee9fed695"));

    kGs.insert(std::pair<int, std::string>(13, " 0"));
    xGs.insert(std::pair<int, std::string>(13, " 423a013f03ff32d7a5ffbcc8e139c62130fdfeb5c6da121bce78049e46bc47d6"));
    yGs.insert(std::pair<int, std::string>(13, " b91ae00fe1e1d970a1179f7bbaf6b3c7720d8ec3524f009ed1236e6d8b548a34"));

    kGs.insert(std::pair<int, std::string>(14, " 0"));
    xGs.insert(std::pair<int, std::string>(14, " 111d6a45ac1fb90508907a7abcd6877649df662f3b3e2741302df6f78416824a"));
    yGs.insert(std::pair<int, std::string>(14, " 696911c478eaffbb90d48dbff065952f070008996daca4ca9a111d42108e9d0"));

    kGs.insert(std::pair<int, std::string>(15, " 0"));
    xGs.insert(std::pair<int, std::string>(15, " 4a4a6dc97ac7c8b8ad795dbebcb9dcff7290b68a5ef74e56ab5edde01bced775"));
    yGs.insert(std::pair<int, std::string>(15, " 529911b016631e72943ef9f739c0f4571de90cdb424742acb2bf8f68a78dd66d"));

    kGs.insert(std::pair<int, std::string>(16, " 0"));
    xGs.insert(std::pair<int, std::string>(16, " 363d90d447b00c9c99ceac05b6262ee053441c7e55552ffe526bad8f83ff4640"));
    yGs.insert(std::pair<int, std::string>(16, " 4e273adfc732221953b445397f3363145b9a89008199ecb62003c7f3bee9de9"));

    kGs.insert(std::pair<int, std::string>(17, " 0"));
    xGs.insert(std::pair<int, std::string>(17, " 4c1b9866ed9a7e9b553973c6c93b02bf0b62fb012edfb59dd2712a5caf92c541"));
    yGs.insert(std::pair<int, std::string>(17, " c1f792d320be8a0f7fbcb753ce56e69cc652ead7e43eb1ad72c4f3fdc68fe020"));

    kGs.insert(std::pair<int, std::string>(18, " 0"));
    xGs.insert(std::pair<int, std::string>(18, " a4083877ba83b12b529a2f3c0780b54e3233edbc1a28f135e0c8f28cbeaaf3d1"));
    yGs.insert(std::pair<int, std::string>(18, " 40e9f612feefbc79b8bf83d69361b3e22001e7576ed1ef90b12b534df0b254b9"));

    kGs.insert(std::pair<int, std::string>(19, " 0"));
    xGs.insert(std::pair<int, std::string>(19, " a804c641d28cc0b53a4e3e1a2f56c86f6e0d880a454203b98cd3db5a7940d33a"));
    yGs.insert(std::pair<int, std::string>(19, " 95be83252b2fa6d03dec2842c16047e81af18ca89cf736a943ce95fa6d46967a"));

    kGs.insert(std::pair<int, std::string>(20, " 0"));
    xGs.insert(std::pair<int, std::string>(20, " 8b4b5f165df3c2be8c6244b5b745638843e4a781a15bcd1b69f79a55dffdf80c"));
    yGs.insert(std::pair<int, std::string>(20, " 4aad0a6f68d308b4b3fbd7813ab0da04f9e336546162ee56b3eff0c65fd4fd36"));

    kGs.insert(std::pair<int, std::string>(21, " 0"));
    xGs.insert(std::pair<int, std::string>(21, " ed0c5ce4e13291718ce17c7ec83c611071af64ee417c997abb3f26714755e4be"));
    yGs.insert(std::pair<int, std::string>(21, " 221a9fc7bc2345bdbf3dad7f5a7ea68049d93925763ddab163f9fa6ea07bf42f"));

    kGs.insert(std::pair<int, std::string>(22, " 0"));
    xGs.insert(std::pair<int, std::string>(22, " faecb013c44ce694b3b15c3f83f1fae8e53254566e0552ced4b6e6c807cec8ab"));
    yGs.insert(std::pair<int, std::string>(22, " cc09b5e90e9ecb57fc2e02c6ec2fb13d9c32b286b85e2e2e8981dfd9ab155070"));

    kGs.insert(std::pair<int, std::string>(23, " 0"));
    xGs.insert(std::pair<int, std::string>(23, " 9bb8a132dcad2f2c8731a0b37cbcafdb3b2dd824f23cd3e07f64eae9ad1b1f7"));
    yGs.insert(std::pair<int, std::string>(23, " 945bb2b2afeee3b9b6f9dd284f863e850f54a840f4752d5364130627c3811c80"));

    kGs.insert(std::pair<int, std::string>(24, " 0"));
    xGs.insert(std::pair<int, std::string>(24, " 723cbaa6e5db996d6bf771c00bd548c7b700dbffa6c0e77bcb6115925232fcda"));
    yGs.insert(std::pair<int, std::string>(24, " 96e867b5595cc498a921137488824d6e2660a0653779494801dc069d9eb39f5f"));

    kGs.insert(std::pair<int, std::string>(25, " 0"));
    xGs.insert(std::pair<int, std::string>(25, " 57efa786437b744d343d7dc45773a3c62d240a43079849071fd383d60ca030d5"));
    yGs.insert(std::pair<int, std::string>(25, " d712db0bd1b48518893627c928de03ec689b6d2ae5e9974ab07ab44274b02f9e"));

    kGs.insert(std::pair<int, std::string>(26, " 0"));
    xGs.insert(std::pair<int, std::string>(26, " 264bbd436a28bc42a2df7e9cd5226cb91080577e327b012a7fafc7770c584dd5"));
    yGs.insert(std::pair<int, std::string>(26, " d87c6fa94ee093b4d4f75ce24c33be226a118243717b8d8de61227937704ab11"));

    kGs.insert(std::pair<int, std::string>(27, " 0"));
    xGs.insert(std::pair<int, std::string>(27, " a94c6524bd40d2bbdac85c056236a79da78bc61fd5bdec9d2bf26bd84b2438e8"));
    yGs.insert(std::pair<int, std::string>(27, " b5201fd992f96280fd79219505019e3a7e5d3c60a0e39b2bc2e2c8dbf18661f4"));

    kGs.insert(std::pair<int, std::string>(28, " 0"));
    xGs.insert(std::pair<int, std::string>(28, " eebfa4d493bebf98ba5feec812c2d3b50947961237a919839a533eca0e7dd7fa"));
    yGs.insert(std::pair<int, std::string>(28, " 5d9a8ca3970ef0f269ee7edaf178089d9ae4cdc3a711f712ddfd4fdae1de8999"));

    kGs.insert(std::pair<int, std::string>(29, " 0"));
    xGs.insert(std::pair<int, std::string>(29, " 381c4ad7a7a97bfda61c6031c118495fc4ea4bc08f6766d676bee90847d297fd"));
    yGs.insert(std::pair<int, std::string>(29, " 936af53b238eeee48f3e5fa709915eccf0451032db939c0093ace3187d493fc5"));

    kGs.insert(std::pair<int, std::string>(30, " 0"));
    xGs.insert(std::pair<int, std::string>(30, " e1efb9cd05adc63bcce10831d9538c479cf1d05fefdd08b2448d70422ede454c"));
    yGs.insert(std::pair<int, std::string>(30, " ecb4530d8af9be7b0154c1ffe477123464e3244a7a2d4c6ad9fd233a8913797"));

    kGs.insert(std::pair<int, std::string>(31, " 0"));
    xGs.insert(std::pair<int, std::string>(31, " 5318f9b1a2697010c5ac235e9af475a8c7e5419f33d47b18d33feeb329eb99a4"));
    yGs.insert(std::pair<int, std::string>(31, " f44ccfeb4beda4195772d93aebb405e8a41f2b40d1e3ec652c726eeefe91f92d"));

    kGs.insert(std::pair<int, std::string>(32, " 0"));
    xGs.insert(std::pair<int, std::string>(32, " 100f44da696e71672791d0a09b7bde459f1215a29b3c03bfefd7835b39a48db0"));
    yGs.insert(std::pair<int, std::string>(32, " cdd9e13192a00b772ec8f3300c090666b7ff4a18ff5195ac0fbd5cd62bc65a09"));

    kGs.insert(std::pair<int, std::string>(33, " 0"));
    xGs.insert(std::pair<int, std::string>(33, " 8c0989f2ceb5c771a8415dff2b4c4199d8d9c8f9237d08084b05284f1e4df706"));
    yGs.insert(std::pair<int, std::string>(33, " fb4dbd044f432034ffd2172cb9dc966c60de6bf5156511aa736ac5a35d72fa98"));

    kGs.insert(std::pair<int, std::string>(34, " 0"));
    xGs.insert(std::pair<int, std::string>(34, " fb8f153c5e266704c4a481743262c0259c528539bc95bc1bb1e63c33dc47bffd"));
    yGs.insert(std::pair<int, std::string>(34, " 6ca27a9dc5e0621816fa11d9b4bccd531dde1389ac542613090a45ddd949b095"));

    kGs.insert(std::pair<int, std::string>(35, " 0"));
    xGs.insert(std::pair<int, std::string>(35, " e747333fd75d51755a0cc9f0a728708465a02c587737a7b8b8fa1b8b4bb2629a"));
    yGs.insert(std::pair<int, std::string>(35, " f2affe0145070c114cc43603804c2581c88376aa6e1a969a9f8d961a6946f6d6"));

    kGs.insert(std::pair<int, std::string>(36, " 0"));
    xGs.insert(std::pair<int, std::string>(36, " e1031be262c7ed1b1dc9227a4a04c017a77f8d4464f3b3852c8acde6e534fd2d"));
    yGs.insert(std::pair<int, std::string>(36, " 9d7061928940405e6bb6a4176597535af292dd419e1ced79a44f18f29456a00d"));

    kGs.insert(std::pair<int, std::string>(37, " 0"));
    xGs.insert(std::pair<int, std::string>(37, " f4b93f224c8089eab9f95dcd0f29b2c9028a6ac5de94d85784e27e36a95c8356"));
    yGs.insert(std::pair<int, std::string>(37, " a67a92ec062962dfb0e5f6a7a40eee90c37ef1344915609abd5861b9be001fd3"));

    kGs.insert(std::pair<int, std::string>(38, " 0"));
    xGs.insert(std::pair<int, std::string>(38, " 9d1aca1fce55236b19622ea025b08b0d51e8512f97e696c20d62fe17b160e8a"));
    yGs.insert(std::pair<int, std::string>(38, " 1153188f5101f0c63e56692ce0d8c27e6fe9e0ee9212b5e534e050c57ca04c44"));

    kGs.insert(std::pair<int, std::string>(39, " 0"));
    xGs.insert(std::pair<int, std::string>(39, " c66c59cc454c2b9e18a2ad793821cde7518b3a93bfc39562e97d7d0475ba7fc2"));
    yGs.insert(std::pair<int, std::string>(39, " d9592fe2bfb30fcfbea4f3ceaac10cb2f00a60ddb15955977ec3c69cf75f5956"));

    kGs.insert(std::pair<int, std::string>(40, " 0"));
    xGs.insert(std::pair<int, std::string>(40, " feea6cae46d55b530ac2839f143bd7ec5cf8b266a41d6af52d5e688d9094696d"));
    yGs.insert(std::pair<int, std::string>(40, " e57c6b6c97dce1bab06e4e12bf3ecd5c981c8957cc41442d3155debf18090088"));

    kGs.insert(std::pair<int, std::string>(41, " 0"));
    xGs.insert(std::pair<int, std::string>(41, " 4d000b621adb87e1c53261af9db2e179141ecae0b331a1870aa4040aee752b08"));
    yGs.insert(std::pair<int, std::string>(41, " 6a0d5b8f18e0d255cb6d825582d972cccb7df5f119c7293a3e72851f48302cea"));

    kGs.insert(std::pair<int, std::string>(42, " 0"));
    xGs.insert(std::pair<int, std::string>(42, " 71f570ca203da05dd6aa262114717128d657a0403e1f1b77f89962fd475c58ef"));
    yGs.insert(std::pair<int, std::string>(42, " eb42415b95dc880dd25557345bc95b8df2445d00c3363e7df8649a72d35d420e"));

    kGs.insert(std::pair<int, std::string>(43, " 0"));
    xGs.insert(std::pair<int, std::string>(43, " a2b7b3629f7bd253b7d282b5c21da01446b4821dc65e76516048b06043ff8359"));
    yGs.insert(std::pair<int, std::string>(43, " 693038941695122d57a937a3f71e29c910d10835046f3835a2397fecfe86fec2"));

    kGs.insert(std::pair<int, std::string>(44, " 0"));
    xGs.insert(std::pair<int, std::string>(44, " da67a91d91049cdcb367be4be6ffca3cfeed657d808583de33fa978bc1ec6cb1"));
    yGs.insert(std::pair<int, std::string>(44, " 9bacaa35481642bc41f463f7ec9780e5dec7adc508f740a17e9ea8e27a68be1d"));

    kGs.insert(std::pair<int, std::string>(45, " 0"));
    xGs.insert(std::pair<int, std::string>(45, " 4dbacd365fa1ef587c0c0cfaaf00d8718bbd9f35ccea5a835ee3cc821fe741c9"));
    yGs.insert(std::pair<int, std::string>(45, " 16c3540e8a51892e7fdcfd59e838299d0cc384a09fc0535f60be10f8338eb623"));

    kGs.insert(std::pair<int, std::string>(46, " 0"));
    xGs.insert(std::pair<int, std::string>(46, " 13d1ffc481509beee68f17d8ff41c2590f4c85f15268605087eda8bab4e218da"));
    yGs.insert(std::pair<int, std::string>(46, " 6008391fa991961dcecb9337b1b758bda4ad01206d5bd127e0db419ddb191c19"));

    kGs.insert(std::pair<int, std::string>(47, " 0"));
    xGs.insert(std::pair<int, std::string>(47, " 219b4f9cef6c60007659c79c45b0533b3cc9d916ce29dbff133b40caa2e96db8"));
    yGs.insert(std::pair<int, std::string>(47, " 24d9c605d959efeaf5a44180c0372a6e394f8ac53e90576527df01a78d3b6bc7"));

    kGs.insert(std::pair<int, std::string>(48, " 0"));
    xGs.insert(std::pair<int, std::string>(48, " 53904faa0b334cdda6e000935ef22151ec08d0f7bb11069f57545ccc1a37b7c0"));
    yGs.insert(std::pair<int, std::string>(48, " 5bc087d0bc80106d88c9eccac20d3c1c13999981e14434699dcb096b022771c8"));

    kGs.insert(std::pair<int, std::string>(49, " 0"));
    xGs.insert(std::pair<int, std::string>(49, " 1a575af9d4146753cf991196316995d2a6ee7aaad0f85ad57cd0f1f38a47ca9"));
    yGs.insert(std::pair<int, std::string>(49, " 3038f1cb8ab20dc3cc55fc52e1bb8698bdb93c5d9f4d7ea667c5df2e77ebcdb7"));

    kGs.insert(std::pair<int, std::string>(50, " 0"));
    xGs.insert(std::pair<int, std::string>(50, " f5f0e0437621d439ca71f5c1b76155d6d3a61a83d3c20c6ee309d755e315565b"));
    yGs.insert(std::pair<int, std::string>(50, " 6b9f4e62be5a052bf62189160df7101aa5bf61bf3ed7e40a678430afdd2ecc82"));

    kGs.insert(std::pair<int, std::string>(51, " 0"));
    xGs.insert(std::pair<int, std::string>(51, " 8f506f0b6c0b6e9a57a7f36d970ca4e347cbc92146227642cbe781d9f5362d33"));
    yGs.insert(std::pair<int, std::string>(51, " 469f955d2afa61719530c5424f1c336848cf925d43bb8eaf30487d0c87fa243f"));

    kGs.insert(std::pair<int, std::string>(52, " 0"));
    xGs.insert(std::pair<int, std::string>(52, " 8e7bcd0bd35983a7719cca7764ca906779b53a043a9b8bcaeff959f43ad86047"));
    yGs.insert(std::pair<int, std::string>(52, " 10b7770b2a3da4b3940310420ca9514579e88e2e47fd68b3ea10047e8460372a"));

    kGs.insert(std::pair<int, std::string>(53, " 0"));
    xGs.insert(std::pair<int, std::string>(53, " 33b35baa195e729dc350f319996950df3bc15b8d3d0389e777d2808bf13f0351"));
    yGs.insert(std::pair<int, std::string>(53, " a58a0185640abf87f9464036248d52bcaa6560efbc889b702bc503cccb8d7418"));

    kGs.insert(std::pair<int, std::string>(54, " 0"));
    xGs.insert(std::pair<int, std::string>(54, " 374deeae22c93f955cb83ad2071f7e2256f6e109cad7bca6d71dc7b24414bb36"));
    yGs.insert(std::pair<int, std::string>(54, " 171165b64fcd4f9916032c06f806f7293828d66300e543217875bea98daf734a"));

    kGs.insert(std::pair<int, std::string>(55, " 0"));
    xGs.insert(std::pair<int, std::string>(55, " 2380c09c7f3aeae57c46e07395aeb0dc944dbaf2b62a9f0c5e8a64ad6ae7d616"));
    yGs.insert(std::pair<int, std::string>(55, " 6f8e86193464956af1598aefd509b09a93af92148f8467560099be48161bbc1a"));

    kGs.insert(std::pair<int, std::string>(56, " 0"));
    xGs.insert(std::pair<int, std::string>(56, " 385eed34c1cdff21e6d0818689b81bde71a7f4f18397e6690a841e1599c43862"));
    yGs.insert(std::pair<int, std::string>(56, " 283bebc3e8ea23f56701de19e9ebf4576b304eec2086dc8cc0458fe5542e5453"));

    kGs.insert(std::pair<int, std::string>(57, " 0"));
    xGs.insert(std::pair<int, std::string>(57, " f6f622083daf54800456be134d5f67d147c82642befc1ce2dc83a27078f2827c"));
    yGs.insert(std::pair<int, std::string>(57, " 1bcd4e817de73a0faf2c5715b367cee7e657ca7448321bf6d15b20b520aaa102"));

    kGs.insert(std::pair<int, std::string>(58, " 0"));
    xGs.insert(std::pair<int, std::string>(58, " fb26e5188f953de2bd70cb3c3d1fc255cd91c3ce7d8c6f369d893209715adcb6"));
    yGs.insert(std::pair<int, std::string>(58, " f3e128811012a34d58e846a719d0176916d2cb31b8b7ab5449dbca3b58ba68f3"));

    kGs.insert(std::pair<int, std::string>(59, " 0"));
    xGs.insert(std::pair<int, std::string>(59, " 8991225911b9132d28f5c6bc763ceab7d18c37060e8bd1d7ed44db7560788c1e"));
    yGs.insert(std::pair<int, std::string>(59, " da8b4d987cc9ac9b27b8763559b136fa36969c84fdef9e11635c42228e8f0ef1"));

    kGs.insert(std::pair<int, std::string>(60, " 0"));
    xGs.insert(std::pair<int, std::string>(60, " 6f9d9b803ecf191637c73a4413dfa180fddf84a5947fbc9c606ed86c3fac3a7"));
    yGs.insert(std::pair<int, std::string>(60, " 7c80c68e603059ba69b8e2a30e45c4d47ea4dd2f5c281002d86890603a842160"));

    kGs.insert(std::pair<int, std::string>(61, " 0"));
    xGs.insert(std::pair<int, std::string>(61, " ae86eeea252b411c1cdc36c284482939da1745e5a7e4da175c9d22744b7fd72d"));
    yGs.insert(std::pair<int, std::string>(61, " 19e993c9707302f962ab0ace589ff0e98d9211551472f7282334cb7a4eee38bc"));

    kGs.insert(std::pair<int, std::string>(62, " 0"));
    xGs.insert(std::pair<int, std::string>(62, " 2248c9f90bbfff55e61d2f8c56dc2c488718be75cf36f2ee7a1474267c169290"));
    yGs.insert(std::pair<int, std::string>(62, " fa0594692d21eed7a506bb55b435ba18e163750235da2be2369d8a12883ea257"));

    kGs.insert(std::pair<int, std::string>(63, " 0"));
    xGs.insert(std::pair<int, std::string>(63, " e11a6e16e05c44074ac11b48d94085d0a99f0877dd1c6f76fd0dac4bb50964e3"));
    yGs.insert(std::pair<int, std::string>(63, " 87d6065b87a2d430e1ad5e2596f0af2417adc6e138318c6f767fbf8b0682bfc8"));

    kGs.insert(std::pair<int, std::string>(64, " 0"));
    xGs.insert(std::pair<int, std::string>(64, " 3322d401243c4e2582a2147c104d6ecbf774d163db0f5e5313b7e0e742d0e6bd"));
    yGs.insert(std::pair<int, std::string>(64, " 56e70797e9664ef5bfb019bc4ddaf9b72805f63ea2873af624f3a2e96c28b2a0"));

    kGs.insert(std::pair<int, std::string>(65, " 0"));
    xGs.insert(std::pair<int, std::string>(65, " 8d26200250cebdae120ef31b04c80cd50d4cddc8eadbcf29fc696d32c0ade462"));
    yGs.insert(std::pair<int, std::string>(65, " ebed3bb4715bf437d31f6f2dc3ee36ba1d4afb4e72678b3ad8e0a8b90f26470c"));

    kGs.insert(std::pair<int, std::string>(66, " 0"));
    xGs.insert(std::pair<int, std::string>(66, " 1238c0766eaebea9ce4068a1f594d03b8ed4930d072d9c8b9164643e1516e633"));
    yGs.insert(std::pair<int, std::string>(66, " 8a9db02dbb271359d6c979e2d1c3dc170946252dcc74022805cdb728c77b7805"));

    kGs.insert(std::pair<int, std::string>(67, " 0"));
    xGs.insert(std::pair<int, std::string>(67, " 271d5b0770cb9c15e7b2ea758a6a11b9cddcd7282b0ec21619b01552788e7a66"));
    yGs.insert(std::pair<int, std::string>(67, " 5d3aa45834e7f491e457d09949ac877fe2a065e3508a824e7a8d7258e03c9727"));

    kGs.insert(std::pair<int, std::string>(68, " 0"));
    xGs.insert(std::pair<int, std::string>(68, " 85672c7d2de0b7da2bd1770d89665868741b3f9af7643397721d74d28134ab83"));
    yGs.insert(std::pair<int, std::string>(68, " 7c481b9b5b43b2eb6374049bfa62c2e5e77f17fcc5298f44c8e3094f790313a6"));

    kGs.insert(std::pair<int, std::string>(69, " 0"));
    xGs.insert(std::pair<int, std::string>(69, " 534ccf6b740f9ec036c1861215c8a61f3b89ea46df2e6d96998b90bc1f17fc25"));
    yGs.insert(std::pair<int, std::string>(69, " d5715cb09c8b2ddb462ae3dd32d543550ae3d277bfdd28ddd71c7f6ecfe86e76"));

    kGs.insert(std::pair<int, std::string>(70, " 0"));
    xGs.insert(std::pair<int, std::string>(70, " a91d1f5cee87b7f3081e142018f8aaed79020d47ecfbc8d2c7170923e8bee8b6"));
    yGs.insert(std::pair<int, std::string>(70, " 748a324ee2df8ee15a7189c8dddad3b2f800569f628cb225003d16aa410644c1"));

    kGs.insert(std::pair<int, std::string>(71, " 0"));
    xGs.insert(std::pair<int, std::string>(71, " c15c8c23d90c8e35c1a214dde2d4383c0735ae45bef61f10aa1a1c255984cf74"));
    yGs.insert(std::pair<int, std::string>(71, " 2ba954d828522235c8dc6f45e25fd7ba47bf772d50b015a2c4a48cd839ccb000"));

    kGs.insert(std::pair<int, std::string>(72, " 0"));
    xGs.insert(std::pair<int, std::string>(72, " 948bf809b1988a46b06c9f1919413b10f9226c60f668832ffd959af60c82a0a"));
    yGs.insert(std::pair<int, std::string>(72, " 53a562856dcb6646dc6b74c5d1c3418c6d4dff08c97cd2bed4cb7f88d8c8e589"));

    kGs.insert(std::pair<int, std::string>(73, " 0"));
    xGs.insert(std::pair<int, std::string>(73, " 26952c7f372e59360d5ce4c66291f0b6ef16c1331e825e51396eb0457e8b000a"));
    yGs.insert(std::pair<int, std::string>(73, " f513ea4c5800a68862bc893d2d688422debe398f653d67318c3d401f05ef705a"));

    kGs.insert(std::pair<int, std::string>(74, " 0"));
    xGs.insert(std::pair<int, std::string>(74, " c62e58e6fc23c5bdbef2be8b131ff243f521196572d6b0e9f102588976134f96"));
    yGs.insert(std::pair<int, std::string>(74, " 4397827d45b1a1678c3d676753141fc5bcfb853563731c3e82277ed4d14cf97e"));

    kGs.insert(std::pair<int, std::string>(75, " 0"));
    xGs.insert(std::pair<int, std::string>(75, " 107460520eec5c741683329a716622b0b81c03200807de973686f8800b188cbb"));
    yGs.insert(std::pair<int, std::string>(75, " abe5d4c09a21598c35326b9b9cf54a11242e0d748dce3da601d7b6361f272124"));

    kGs.insert(std::pair<int, std::string>(76, " 0"));
    xGs.insert(std::pair<int, std::string>(76, " 6260ce7f461801c34f067ce0f02873a8f1b0e44dfc69752accecd819f38fd8e8"));
    yGs.insert(std::pair<int, std::string>(76, " bc2da82b6fa5b571a7f09049776a1ef7ecd292238051c198c1a84e95b2b4ae17"));

    kGs.insert(std::pair<int, std::string>(77, " 0"));
    xGs.insert(std::pair<int, std::string>(77, " 85d8da4748ad1a73dec8409be84f1a1316e65c5196aad27e0766746f3d477c2d"));
    yGs.insert(std::pair<int, std::string>(77, " 58948b53665c6690586b536531efc7bc94b0a02033c4d5a62079816fc7d1dd70"));

    kGs.insert(std::pair<int, std::string>(78, " 0"));
    xGs.insert(std::pair<int, std::string>(78, " 8e2a7166e7ec4b968c0892e9cc3ee3ee4d1e7e100fdc47f04850312d6c0b80d9"));
    yGs.insert(std::pair<int, std::string>(78, " eadb0ba9ae2cbe592cedd29b716a9d485297b688d706349a49c61f2ad6b29f50"));

    kGs.insert(std::pair<int, std::string>(79, " 0"));
    xGs.insert(std::pair<int, std::string>(79, " 769bc75842bff58edc8366ecd78f8950ee4ab2e81359d90f9921fa3d2c4561be"));
    yGs.insert(std::pair<int, std::string>(79, " 4bf817362fe783bac8dce4cef73f5d4741a177767b7873add5920bffb0d9685f"));

    kGs.insert(std::pair<int, std::string>(80, " 0"));
    xGs.insert(std::pair<int, std::string>(80, " e5037de0afc1d8d43d8348414bbf4103043ec8f575bfdc432953cc8d2037fa2d"));
    yGs.insert(std::pair<int, std::string>(80, " 4571534baa94d3b5f9f98d09fb990bddbd5f5b03ec481f10e0e5dc841d755bda"));

    kGs.insert(std::pair<int, std::string>(81, " 0"));
    xGs.insert(std::pair<int, std::string>(81, " a5e00da467fd5494f40b6cf7d2d61b3ec3ab217c792a2ddb8c63c8c79e3d34ef"));
    yGs.insert(std::pair<int, std::string>(81, " 98fe5f5e5608555421726fe99bf43d25b60dcfe790900acb855c5ce2f7adb4c"));

    kGs.insert(std::pair<int, std::string>(82, " 0"));
    xGs.insert(std::pair<int, std::string>(82, " a99415f5ef3a2b403519f4bb1c9bfbc46d4afd2e4477572ae6737160d7b91252"));
    yGs.insert(std::pair<int, std::string>(82, " 82d0e64cae81f84bb9e2f10f24f6f6b6899a16ad590f4ddd73a377ac4bedc264"));

    kGs.insert(std::pair<int, std::string>(83, " 0"));
    xGs.insert(std::pair<int, std::string>(83, " b56f4e9f9e4fd1fc7d8edde098f935f84c750d705f0c132bd8c465b66a540f17"));
    yGs.insert(std::pair<int, std::string>(83, " 32e8e53429cca856d3dc11adf0582d1d21d42963cbcca85446a2fcae0200102d"));

    kGs.insert(std::pair<int, std::string>(84, " 0"));
    xGs.insert(std::pair<int, std::string>(84, " e06372b0f4a207adf5ea905e8f1771b4e7e8dbd1c6a6c5b725866a0ae4fce725"));
    yGs.insert(std::pair<int, std::string>(84, " 7a908974bce18cfe12a27bb2ad5a488cd7484a7787104870b27034f94eee31dd"));

    kGs.insert(std::pair<int, std::string>(85, " 0"));
    xGs.insert(std::pair<int, std::string>(85, " eac134ca2046b8f9c8dbd304fad3f3c045ebfdb4ec6ed3cfe09aee43ed2ff3e"));
    yGs.insert(std::pair<int, std::string>(85, " 49630dbe79359b4245bf103bf2b11799ac19f696b7f21376e17206207d210988"));

    kGs.insert(std::pair<int, std::string>(86, " 0"));
    xGs.insert(std::pair<int, std::string>(86, " d6788590731fea198392119d7adbb41ff5948a7804c85b17476706e4dfbfa4dc"));
    yGs.insert(std::pair<int, std::string>(86, " 28eaa8c89d5063c4940ef5c6d21c13aa6206f1c4ddc9a07cca7bcd6bbd3b5406"));

    kGs.insert(std::pair<int, std::string>(87, " 0"));
    xGs.insert(std::pair<int, std::string>(87, " 6930fccbd9a040974abf210f12b71d4bc7b1a6205599b01a7275fb40e48ff9b3"));
    yGs.insert(std::pair<int, std::string>(87, " 7f02ae94b94701eada30fcdb875f6d78090f9b13e4acc51acfddab5f8ee96a4e"));

    kGs.insert(std::pair<int, std::string>(88, " 0"));
    xGs.insert(std::pair<int, std::string>(88, " 213c7a715cd5d45358d0bbf9dc0ce02204b10bdde2a3f58540ad6908d0559754"));
    yGs.insert(std::pair<int, std::string>(88, " 4b6dad0b5ae462507013ad06245ba190bb4850f5f36a7eeddff2c27534b458f2"));

    kGs.insert(std::pair<int, std::string>(89, " 0"));
    xGs.insert(std::pair<int, std::string>(89, " 1c5e548132b49a7f66ae9fed8323480e0d1ab974622e7cf08993895e0ec87fac"));
    yGs.insert(std::pair<int, std::string>(89, " 4ffcf60f837f468f2bb959fa1d4c2ad3a3deaceb26fe324c555d7b3d5fc2d4ef"));

    kGs.insert(std::pair<int, std::string>(90, " 0"));
    xGs.insert(std::pair<int, std::string>(90, " 46276d0602c5668ddef6e94210bbc7ce1f901c19fed5c970e20fcba1d4531dbc"));
    yGs.insert(std::pair<int, std::string>(90, " e0f7f24d44c75b84a292287570ded99498badfbffe1bc99af8730099686b8e2"));

    kGs.insert(std::pair<int, std::string>(91, " 0"));
    xGs.insert(std::pair<int, std::string>(91, " efea68eca7a6c24f4e65eb211c3191636850e0acdc78d8996114ef13522f001d"));
    yGs.insert(std::pair<int, std::string>(91, " aab847869d583c14da150307a3719a17e413959fb3848771c128419f73bc4415"));

    kGs.insert(std::pair<int, std::string>(92, " 0"));
    xGs.insert(std::pair<int, std::string>(92, " 4e7c272a7af4b34e8dbb9352a5419a87e2838c70adc62cddf0cc3a3b08fbd53c"));
    yGs.insert(std::pair<int, std::string>(92, " 17749c766c9d0b18e16fd09f6def681b530b9614bff7dd33e0b3941817dcaae6"));

    kGs.insert(std::pair<int, std::string>(93, " 0"));
    xGs.insert(std::pair<int, std::string>(93, " 899017b02696888f268a269f4e385d9c9b11f25a1bef8790e2821e6e7c6e1b4d"));
    yGs.insert(std::pair<int, std::string>(93, " 43ae2cdab5b334f0bb45798336358bfae4e51bc0f932b212009aebdad814ab2b"));

    kGs.insert(std::pair<int, std::string>(94, " 0"));
    xGs.insert(std::pair<int, std::string>(94, " 67f644f76e905fd4a8f4728e63227f0e2831f5bf91b583a8af2635a17e5f712f"));
    yGs.insert(std::pair<int, std::string>(94, " b833d68f66445d04f05adeb7b586cf785e0e1488f7d36198d68acb5e707160e5"));

    kGs.insert(std::pair<int, std::string>(95, " 0"));
    xGs.insert(std::pair<int, std::string>(95, " 327f876c93652555fa80a054968b4712930dc93012ee6b8dc10263ed3b89a762"));
    yGs.insert(std::pair<int, std::string>(95, " b2d404eab3524026b09969255e1997b975535070febd7dfe9c9fd959b9203301"));

    kGs.insert(std::pair<int, std::string>(96, " 0"));
    xGs.insert(std::pair<int, std::string>(96, " fea74e3dbe778b1b10f238ad61686aa5c76e3db2be43057632427e2840fb27b6"));
    yGs.insert(std::pair<int, std::string>(96, " 6e0568db9b0b13297cf674deccb6af93126b596b973f7b77701d3db7f23cb96f"));

    kGs.insert(std::pair<int, std::string>(97, " 0"));
    xGs.insert(std::pair<int, std::string>(97, " ed9441c8304280ff180e03d850e8cd0ebb570ee5de3730488fd97c961f9756e4"));
    yGs.insert(std::pair<int, std::string>(97, " 3dbe9e9efe8bfa19afa176128b13911e09f23774fe4de98bff0e09f93f3abfae"));

    kGs.insert(std::pair<int, std::string>(98, " 0"));
    xGs.insert(std::pair<int, std::string>(98, " 29d9698ee67a7c3fc9fed3f624b487515b10bdd84fab4d3015bad033d51cf119"));
    yGs.insert(std::pair<int, std::string>(98, " 7fd02c517dc82b45277a125404f1c96fb89c940e93a7c2963c88740575056339"));

    kGs.insert(std::pair<int, std::string>(99, " 0"));
    xGs.insert(std::pair<int, std::string>(99, " 126b57d05013936d6f3fb7bd33580a31fd453e4a86060cff467c44537f422491"));
    yGs.insert(std::pair<int, std::string>(99, " c1a7dc13061662c2e3c4a3eba2bf3fb0e148bac30bf39347afa31f199da3ef84"));

    kGs.insert(std::pair<int, std::string>(100, " 0"));
    xGs.insert(std::pair<int, std::string>(100, " 76e64113f677cf0e10a2570d599968d31544e179b760432952c02a4417bdde39"));
    yGs.insert(std::pair<int, std::string>(100, " c90ddf8dee4e95cf577066d70681f0d35e2a33d2b56d2032b4b1752d1901ac01"));

    kGs.insert(std::pair<int, std::string>(101, " 0"));
    xGs.insert(std::pair<int, std::string>(101, " 708a530e9e52c73bee87c9d88161c810005d57622c29ae691cf999a83a1187a5"));
    yGs.insert(std::pair<int, std::string>(101, " 9b884811e1f9a897fa9656dcbb6d38283ecda73c6d353e8a58a4f19b473db9c0"));

    kGs.insert(std::pair<int, std::string>(102, " 0"));
    xGs.insert(std::pair<int, std::string>(102, " 19cf034fc48b3be219bd648395e462cf9f374b6d86b2b59e2e1b16c6cde4f5be"));
    yGs.insert(std::pair<int, std::string>(102, " 28e32b06a15ab466c3b4be68ab181947ef91d1c93f0f1c0c0a91532b6f321af2"));

    kGs.insert(std::pair<int, std::string>(103, " 0"));
    xGs.insert(std::pair<int, std::string>(103, " af6c44a078cb5f0d7c719c2f8397f576ee93bd034bea2219e3abc209d17cf3e8"));
    yGs.insert(std::pair<int, std::string>(103, " 784096fe85d4b30af9e73153cb246dfec362aea7ca0d435b8add0601751baea"));

    kGs.insert(std::pair<int, std::string>(104, " 0"));
    xGs.insert(std::pair<int, std::string>(104, " c738c56b03b2abe1e8281baa743f8f9a8f7cc643df26cbee3ab150242bcbb891"));
    yGs.insert(std::pair<int, std::string>(104, " 893fb578951ad2537f718f2eacbfbbbb82314eef7880cfe917e735d9699a84c3"));

    kGs.insert(std::pair<int, std::string>(105, " 0"));
    xGs.insert(std::pair<int, std::string>(105, " 5578845ecd7c037435b32a6992e7aa94647197ea49b8c9e4ddaab0784662ab1b"));
    yGs.insert(std::pair<int, std::string>(105, " e61d07978b6de2c3cea6d0a51d2a4053f653a7746a5d64de316d18f3056f3511"));

    kGs.insert(std::pair<int, std::string>(106, " 0"));
    xGs.insert(std::pair<int, std::string>(106, " 47f3383888a364cc4abfa3bc1d0ceccd22f12354fce3996094f869b8948b6c29"));
    yGs.insert(std::pair<int, std::string>(106, " 48ca9a8d0f032937190e48675b416c7118bb499588f994a81edee1120e537ef9"));

    kGs.insert(std::pair<int, std::string>(107, " 0"));
    xGs.insert(std::pair<int, std::string>(107, " c0c01f34ae41b8cfe466b4c9c6a5d5f614f570d6fcbef768a81a6c8f05ff4adb"));
    yGs.insert(std::pair<int, std::string>(107, " b84f5bee4357f5c7c937a0b4075b8cecdbc43d170d15b85fc4eff73ac351065"));

    kGs.insert(std::pair<int, std::string>(108, " 0"));
    xGs.insert(std::pair<int, std::string>(108, " d895626548b65b81e264c7637c972877d1d72e5f3a925014372e9f6588f6c14b"));
    yGs.insert(std::pair<int, std::string>(108, " febfaa38f2bc7eae728ec60818c340eb03428d632bb067e179363ed75d7d991f"));

    kGs.insert(std::pair<int, std::string>(109, " 0"));
    xGs.insert(std::pair<int, std::string>(109, " fd136eef8971044e8a3a43622003a26703ecaf7a0ec40c3fba5b594b77078424"));
    yGs.insert(std::pair<int, std::string>(109, " 218da834f3c652cc67a1d191b5c5efa57cf2b1f78a2adfa8cd61eeefc671ddf1"));

    kGs.insert(std::pair<int, std::string>(110, " 0"));
    xGs.insert(std::pair<int, std::string>(110, " d99e8e9dd9638d140e9cca5367519f861b7003a0d43f024a5f1d84ec8db1cb3c"));
    yGs.insert(std::pair<int, std::string>(110, " 36dc19ad1cc0a3a7a945bb321bceba6e6286fef8ffc8765cd88a29e36b8637a7"));

    kGs.insert(std::pair<int, std::string>(111, " 0"));
    xGs.insert(std::pair<int, std::string>(111, " 3fdf1619a198317a1bd8a54e5b09191d203351e0440e636fd46f68d3c385172"));
    yGs.insert(std::pair<int, std::string>(111, " 408d02c06e5c12c3fe470c7d3c8573755b9b929e90e7232b79ac67f0fccb9794"));

    kGs.insert(std::pair<int, std::string>(112, " 0"));
    xGs.insert(std::pair<int, std::string>(112, " b8da94032a957518eb0f6433571e8761ceffc73693e84edd49150a564f676e03"));
    yGs.insert(std::pair<int, std::string>(112, " 2804dfa44805a1e4d7c99cc9762808b092cc584d95ff3b511488e4e74efdf6e7"));

    kGs.insert(std::pair<int, std::string>(113, " 0"));
    xGs.insert(std::pair<int, std::string>(113, " 6d36d105ed8cc5ce53f2cb698ab620f9469a3e5cb25bf6e6d413f414c5af726a"));
    yGs.insert(std::pair<int, std::string>(113, " e4ba5c34e377669e72d8c66c95c50029dcc59936b4108a35c570491a13f9fc7d"));

    kGs.insert(std::pair<int, std::string>(114, " 0"));
    xGs.insert(std::pair<int, std::string>(114, " 3ab6bde10cd3ac0cd06883fa66f0b0e3eb1309c0534b812286e2a30ca540db99"));
    yGs.insert(std::pair<int, std::string>(114, " baca62079be871d7fc3117a96a13e99c38d137b0e369c043e6873fe31bda78a3"));

    kGs.insert(std::pair<int, std::string>(115, " 0"));
    xGs.insert(std::pair<int, std::string>(115, " 796634e3f1ad56f0fdba069d9d07bce2ba2fd4f373ddd3ba7777bf279f1048da"));
    yGs.insert(std::pair<int, std::string>(115, " 4d8ee2b6cfb20b8956de74735a7927f2532576d8cfd74862e8f9be24a106cf01"));

    kGs.insert(std::pair<int, std::string>(116, " 0"));
    xGs.insert(std::pair<int, std::string>(116, " e80fea14441fb33a7d8adab9475d7fab2019effb5156a792f1a11778e3c0df5d"));
    yGs.insert(std::pair<int, std::string>(116, " eed1de7f638e00771e89768ca3ca94472d155e80af322ea9fcb4291b6ac9ec78"));

    kGs.insert(std::pair<int, std::string>(117, " 0"));
    xGs.insert(std::pair<int, std::string>(117, " 440ca1f08ea41265981ac4ed1efe7a37122dcc3877d2f9162db0e78b0f83cd58"));
    yGs.insert(std::pair<int, std::string>(117, " a6c8b0d2cd5ee122af8954dc9d4e2f02a21e4d4269c0a260b07bc069b88a3f4b"));

    kGs.insert(std::pair<int, std::string>(118, " 0"));
    xGs.insert(std::pair<int, std::string>(118, " f694cbaf2b966c1cc5f7f829d3a907819bc70ebcc1b229d9e81bda2712998b10"));
    yGs.insert(std::pair<int, std::string>(118, " 40a63eba61bef03d633c5ffacc46d82aeb6c64c3183c2a47f6788b1700f05e51"));

    kGs.insert(std::pair<int, std::string>(119, " 0"));
    xGs.insert(std::pair<int, std::string>(119, " 8b6e862a3556684850b6d4f439a2595047abf695c08b6414f95a13358dd553fd"));
    yGs.insert(std::pair<int, std::string>(119, " ea5e08910ed11cb40d10bc2df4eb9fa124ac3c5a183383d0d803dad33e9be5ed"));

    kGs.insert(std::pair<int, std::string>(120, " 0"));
    xGs.insert(std::pair<int, std::string>(120, " a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070"));
    yGs.insert(std::pair<int, std::string>(120, " 7370f91cfb67e4f5081809fa25d40f9b1735dbf7c0a11a130c0d1a041e177ea1"));

    kGs.insert(std::pair<int, std::string>(121, " 0"));
    xGs.insert(std::pair<int, std::string>(121, " 27e1e59cff79f049f3e8d2419e0bff74b43965004c34b5d811420316f24ba5ae"));
    yGs.insert(std::pair<int, std::string>(121, " 310b26a6c804e209ee1b5e3cfc79df05df48a1a69afa63f784a5bfee883a45b3"));

    kGs.insert(std::pair<int, std::string>(122, " 0"));
    xGs.insert(std::pair<int, std::string>(122, " c712e7a5f6864aee16588ec3892d7e4f5a39adde84fbfb4f9969175c9caed7ae"));
    yGs.insert(std::pair<int, std::string>(122, " 49644107516363b365ed4b82311dd9e5380d8e544b0ce63784d148aa46156294"));

    kGs.insert(std::pair<int, std::string>(123, " 0"));
    xGs.insert(std::pair<int, std::string>(123, " bfc0504a4b3235d065c0d426b8675fcb2c85d6f58275d791b43e1fe44a6db03"));
    yGs.insert(std::pair<int, std::string>(123, " 1955467a6c34f3453fb8ec7f94a6c99237427197345d4f0558ac8d1a464b8542"));

    kGs.insert(std::pair<int, std::string>(124, " 0"));
    xGs.insert(std::pair<int, std::string>(124, " 90ad85b389d6b936463f9d0512678de208cc330b11307fffab7ac63e3fb04ed4"));
    yGs.insert(std::pair<int, std::string>(124, " e507a3620a38261affdcbd9427222b839aefabe1582894d991d4d48cb6ef150"));

    kGs.insert(std::pair<int, std::string>(125, " 0"));
    xGs.insert(std::pair<int, std::string>(125, " 7e2cd40ef8c94077f44b1d1548425e3d7e125be646707bad2818b0eda7dc0151"));
    yGs.insert(std::pair<int, std::string>(125, " 905b75082adcfab382a61a8b321ef95d889bee40aeee082c9a3bc53920721ec7"));

    kGs.insert(std::pair<int, std::string>(126, " 0"));
    xGs.insert(std::pair<int, std::string>(126, " a146f52195bedace21c975bbd1ef52a79c636bf9db853cf90e103ae41345e597"));
    yGs.insert(std::pair<int, std::string>(126, " a5a99b0ab053feb09ae95dd2dbb31b40ea67a5b221f094b07675676af45a770a"));

    kGs.insert(std::pair<int, std::string>(127, " 0"));
    xGs.insert(std::pair<int, std::string>(127, " d24c75a1cf1993b9bcfbf9dab25a8114dbde421efeccc4e20cbb53fc4ce45444"));
    yGs.insert(std::pair<int, std::string>(127, " 58fe1d2de84dc1d1cfcb7d1810e5a78abf7593f499f1e524cb93246987dd4a57"));

    kGs.insert(std::pair<int, std::string>(128, " 0"));
    xGs.insert(std::pair<int, std::string>(128, " 8f68b9d2f63b5f339239c1ad981f162ee88c5678723ea3351b7b444c9ec4c0da"));
    yGs.insert(std::pair<int, std::string>(128, " 662a9f2dba063986de1d90c2b6be215dbbea2cfe95510bfdf23cbf79501fff82"));

    kGs.insert(std::pair<int, std::string>(129, " 0"));
    xGs.insert(std::pair<int, std::string>(129, " 4d49aefd784e8158fcafebe77fd9af59d89858ade7627eaee6847df84cf27076"));
    yGs.insert(std::pair<int, std::string>(129, " cd32fc59a10dd135e723f210359ca6f06e0f2d1a7df4d8466b90b66203aa781e"));

    kGs.insert(std::pair<int, std::string>(130, " 0"));
    xGs.insert(std::pair<int, std::string>(130, " 7564539e85d56f8537d6619e1f5c5aa78d2a3de0889d1d4ee8dbcb5729b62026"));
    yGs.insert(std::pair<int, std::string>(130, " c1d685413749b3c65231df524a722925684aacd954b79f334172c8fadace0cf3"));

    kGs.insert(std::pair<int, std::string>(131, " 0"));
    xGs.insert(std::pair<int, std::string>(131, " 210a917ad9df27796746ff301ad9ccc878f61a5f1ff4082b5364dacd57b4a278"));
    yGs.insert(std::pair<int, std::string>(131, " 670e1b5450b5e57b7a39be81f8d6737d3789e61aaff20bfc7f2713fd0c7b2231"));

    kGs.insert(std::pair<int, std::string>(132, " 0"));
    xGs.insert(std::pair<int, std::string>(132, " e4f3fb0176af85d65ff99ff9198c36091f48e86503681e3e6686fd5053231e11"));
    yGs.insert(std::pair<int, std::string>(132, " 1e63633ad0ef4f1c1661a6d0ea02b7286cc7e74ec951d1c9822c38576feb73bc"));

    kGs.insert(std::pair<int, std::string>(133, " 0"));
    xGs.insert(std::pair<int, std::string>(133, " 4b30cbb7686773e01ec64110abdb362f88531a825ba172953bfee2233bcdaf2f"));
    yGs.insert(std::pair<int, std::string>(133, " 74c6350265bb629b6f9e2c5777c3c4a91fdf3c81e434857568033d463d26b5b7"));

    kGs.insert(std::pair<int, std::string>(134, " 0"));
    xGs.insert(std::pair<int, std::string>(134, " cbb434aa7ae1700dcd15b20b17464817ec11715050e0fa192ffe9c29a673059f"));
    yGs.insert(std::pair<int, std::string>(134, " 4a1a200ab4dabd17562d492338b5dfad41d45e4f0ad5f845b7da9642227c070c"));

    kGs.insert(std::pair<int, std::string>(135, " 0"));
    xGs.insert(std::pair<int, std::string>(135, " f478056d9c102c1cd06d7b1e7557244c6d9cdac5874610e94d4786e106de12c0"));
    yGs.insert(std::pair<int, std::string>(135, " 7f09e610f33e3946e68095e01068694c26c17ef609ab92d769a76ce6ca5361fe"));

    kGs.insert(std::pair<int, std::string>(136, " 0"));
    xGs.insert(std::pair<int, std::string>(136, " 8c00fa9b18ebf331eb961537a45a4266c7034f2f0d4e1d0716fb6eae20eae29e"));
    yGs.insert(std::pair<int, std::string>(136, " efa47267fea521a1a9dc343a3736c974c2fadafa81e36c54e7d2a4c66702414b"));

    kGs.insert(std::pair<int, std::string>(137, " 0"));
    xGs.insert(std::pair<int, std::string>(137, " 24cfc0176da2b46fa8bb5bf9636be1effd7e297f29122fb3e84c9ab0c18ada5f"));
    yGs.insert(std::pair<int, std::string>(137, " ebff8fbb079c61a69868714d5deda927ed959ca1a4f814f268fa6139978a586b"));

    kGs.insert(std::pair<int, std::string>(138, " 0"));
    xGs.insert(std::pair<int, std::string>(138, " 4a7d58d4b9bc82ea2ded72a1292ec616ddd67fc7f057edf103189594679da2"));
    yGs.insert(std::pair<int, std::string>(138, " b98ac5b76702cb75e6b1d8147ec71b3b71c3b494963fa28a4877f484779ffe26"));

    kGs.insert(std::pair<int, std::string>(139, " 0"));
    xGs.insert(std::pair<int, std::string>(139, " ee7d69c4cbd001c7fc76c5e2c066ce4996f8808a1e07b2a9ccf34eadc87c4b65"));
    yGs.insert(std::pair<int, std::string>(139, " ecc8626ec1a413821a192abf030f2ee2c33e8999bae942e523e8f44ed136a95a"));

    kGs.insert(std::pair<int, std::string>(140, " 0"));
    xGs.insert(std::pair<int, std::string>(140, " e7a26ce69dd4829f3e10cec0a9e98ed3143d084f308b92c0997fddfc60cb3e41"));
    yGs.insert(std::pair<int, std::string>(140, " 2a758e300fa7984b471b006a1aafbb18d0a6b2c0420e83e20e8a9421cf2cfd51"));

    kGs.insert(std::pair<int, std::string>(141, " 0"));
    xGs.insert(std::pair<int, std::string>(141, " f5cafaba036bf8d00d38bfb6772089f5203c35e4d6e32fa9d97e5b917b4ae861"));
    yGs.insert(std::pair<int, std::string>(141, " 19e83b8a022a6d817bff9904640839159b3b2a9c552f05f3cc9c239c0d82239c"));

    kGs.insert(std::pair<int, std::string>(142, " 0"));
    xGs.insert(std::pair<int, std::string>(142, " e9389024ceb63f1f12df5156d7e805428f9e509c494c982084fd4cd7bd2a9651"));
    yGs.insert(std::pair<int, std::string>(142, " 8648688723726595f9287abaf671aaf18d7110cec6770bfefefde2b75e786824"));

    kGs.insert(std::pair<int, std::string>(143, " 0"));
    xGs.insert(std::pair<int, std::string>(143, " 264559d87829256bed116900d82d0c379f0e4d1253c68e6fcf2d41ae7cddab8b"));
    yGs.insert(std::pair<int, std::string>(143, " 79e5bd1926d3512cef7bc637034072d77a8631af39caf1e6c9f64b45001de473"));

    kGs.insert(std::pair<int, std::string>(144, " 0"));
    xGs.insert(std::pair<int, std::string>(144, " b6459e0ee3662ec8d23540c223bcbdc571cbcb967d79424f3cf29eb3de6b80ef"));
    yGs.insert(std::pair<int, std::string>(144, " 67c876d06f3e06de1dadf16e5661db3c4b3ae6d48e35b2ff30bf0b61a71ba45"));

    kGs.insert(std::pair<int, std::string>(145, " 0"));
    xGs.insert(std::pair<int, std::string>(145, " e5d8e8f0d9823c88e4d36f7301f41593b6890576be79c211253ef375033eb51f"));
    yGs.insert(std::pair<int, std::string>(145, " 4dc1e9b7861e3e04abb16a57d8feeef0e509dc46d9f0f54979d5bd965a62a2d9"));

    kGs.insert(std::pair<int, std::string>(146, " 0"));
    xGs.insert(std::pair<int, std::string>(146, " a9ca27f77dbc8c3dc56b0f7321bae0ddab66be4fa8a3011737a676480f155e64"));
    yGs.insert(std::pair<int, std::string>(146, " f4bb335678fb14d4d197d2246c02d004875d41821bcaf0ae1f3f333c561b3297"));

    kGs.insert(std::pair<int, std::string>(147, " 0"));
    xGs.insert(std::pair<int, std::string>(147, " 68fb71800686d7f25eba105611cfe7591f478e847f51cee06d4bc629d6ee247c"));
    yGs.insert(std::pair<int, std::string>(147, " cd12d23462dd963673735427501b0c079a8d580b04c73c9dae1f822d1a01865d"));

    kGs.insert(std::pair<int, std::string>(148, " 0"));
    xGs.insert(std::pair<int, std::string>(148, " d68a80c8280bb840793234aa118f06231d6f1fc67e73c5a5deda0f5b496943e8"));
    yGs.insert(std::pair<int, std::string>(148, " db8ba9fff4b586d00c4b1f9177b0e28b5b0e7b8f7845295a294c84266b133120"));

    kGs.insert(std::pair<int, std::string>(149, " 0"));
    xGs.insert(std::pair<int, std::string>(149, " f16a409c677a40be402f8efb3752373caced053c6f702b828bda222ca412b6fd"));
    yGs.insert(std::pair<int, std::string>(149, " 2a41311714532799d7a6a75a74e30e4e16540659249ebca4268dae77eca052da"));

    kGs.insert(std::pair<int, std::string>(150, " 0"));
    xGs.insert(std::pair<int, std::string>(150, " 4154b506ab766f42fbe37f699976f84db89f4f2f6bed98325c1a0b6e326dd4e4"));
    yGs.insert(std::pair<int, std::string>(150, " 23ad075043c5988894c6e44d61025ff6414ea9d9d1e22dd46c859295075ded1c"));

    kGs.insert(std::pair<int, std::string>(151, " 0"));
    xGs.insert(std::pair<int, std::string>(151, " b73c652769cc95c1080a8d4d0b5956ea93e86e49fc727ddf4c51a7a63f7f0246"));
    yGs.insert(std::pair<int, std::string>(151, " 9a67db107174ca9d4b535893c5b6c1ea1a0d72e4c6e554e5597e5164ea2a407b"));

    kGs.insert(std::pair<int, std::string>(152, " 0"));
    xGs.insert(std::pair<int, std::string>(152, " 324aed7df65c804252dc0270907a30b09612aeb973449cea4095980fc28d3d5d"));
    yGs.insert(std::pair<int, std::string>(152, " 648a365774b61f2ff130c0c35aec1f4f19213b0c7e332843967224af96ab7c84"));

    kGs.insert(std::pair<int, std::string>(153, " 0"));
    xGs.insert(std::pair<int, std::string>(153, " 32c9331ea26f490228d32681880d7203f72b3e4a8de0db1fa8f38381b2919749"));
    yGs.insert(std::pair<int, std::string>(153, " d7cd272b34209cb5695a2f02b6f3dbb8268a4abdae39ab09631e97b0f290b5e3"));

    kGs.insert(std::pair<int, std::string>(154, " 0"));
    xGs.insert(std::pair<int, std::string>(154, " eb292f3b3b9837854a02f6a70fec6b1c69c161b6e1846b8e1e1c22527b9795e4"));
    yGs.insert(std::pair<int, std::string>(154, " 8c43c25a96eebe801696634af145835b57131d7509111c6f5b7e9d2fae53a0fe"));

    kGs.insert(std::pair<int, std::string>(155, " 0"));
    xGs.insert(std::pair<int, std::string>(155, " a65a3a01df3b5ef2e620d4310049fbe14d71457f19d1ed35aea39d5789303fdd"));
    yGs.insert(std::pair<int, std::string>(155, " 798ea0940cff5c6fb8f43d8d90ed2c7686861d024faed3cadad44a8d02e68703"));

    kGs.insert(std::pair<int, std::string>(156, " 0"));
    xGs.insert(std::pair<int, std::string>(156, " 4df9c14919cde61f6d51dfdbe5fee5dceec4143ba8d1ca888e8bd373fd054c96"));
    yGs.insert(std::pair<int, std::string>(156, " 35ec51092d8728050974c23a1d85d4b5d506cdc288490192ebac06cad10d5d"));

    kGs.insert(std::pair<int, std::string>(157, " 0"));
    xGs.insert(std::pair<int, std::string>(157, " ed32cad8d2cc998cd25317d4e4b87088e9de4554e57a8d70c0c6b0fc1da49e04"));
    yGs.insert(std::pair<int, std::string>(157, " 129fef5f1d030204a541ca375859d20b52da9facb49fab7db63120d17c1db9e0"));

    kGs.insert(std::pair<int, std::string>(158, " 0"));
    xGs.insert(std::pair<int, std::string>(158, " e821ab724d6360f18049e4111c70366e28c36dcb63c34016cb7418d4e883f855"));
    yGs.insert(std::pair<int, std::string>(158, " adefcbf863f53ce367d0d4115416cf598b3b19c614ec23efed4e0c6a59852ddf"));

    kGs.insert(std::pair<int, std::string>(159, " 0"));
    xGs.insert(std::pair<int, std::string>(159, " 3f0d8994e51ad212f455452fbc9693a72f14a547af3806e9fbff59eeb441742e"));
    yGs.insert(std::pair<int, std::string>(159, " fbd76c23f28c3dc445e5cb0e847a6e0b1e205e2c3ad13d958c65363bcfecadbe"));

    kGs.insert(std::pair<int, std::string>(160, " 0"));
    xGs.insert(std::pair<int, std::string>(160, " 9c3919a84a474870faed8a9c1cc66021523489054d7f0308cbfc99c8ac1f98cd"));
    yGs.insert(std::pair<int, std::string>(160, " ddb84f0f4a4ddd57584f044bf260e641905326f76c64c8e6be7e5e03d4fc599d"));

    kGs.insert(std::pair<int, std::string>(161, " 0"));
    xGs.insert(std::pair<int, std::string>(161, " 2e3c05326255d80f0a42fc69d5c92aa40cd326a53e8535f0435efb7b694a09ec"));
    yGs.insert(std::pair<int, std::string>(161, " 1ff891656c6fb5bddae240b82fc1abe048a53c707b66512534868188c7327e"));

    kGs.insert(std::pair<int, std::string>(162, " 0"));
    xGs.insert(std::pair<int, std::string>(162, " e8e2a24ccfa41587ae15fb7e3e24dda433710316a1908934205f19a2ab9c7ce6"));
    yGs.insert(std::pair<int, std::string>(162, " 46c983ce0c6f5d1b4caf2b2b3bee20596e09e603b5c27a73b2c01eb68836267c"));

    kGs.insert(std::pair<int, std::string>(163, " 0"));
    xGs.insert(std::pair<int, std::string>(163, " a7549aac5d8573c2b2f0a38b170032a212acaf92383d5b5f5b0d39668ac7b3c2"));
    yGs.insert(std::pair<int, std::string>(163, " bd17d1b90d1c2415335a1d70c1947d2b5d6b5115537116dffa0c91719287eaef"));

    kGs.insert(std::pair<int, std::string>(164, " 0"));
    xGs.insert(std::pair<int, std::string>(164, " 6057170b1dd12fdf8de05f281d8e06bb91e1493a8b91d4cc5a21382120a959e5"));
    yGs.insert(std::pair<int, std::string>(164, " 9a1af0b26a6a4807add9a2daf71df262465152bc3ee24c65e899be932385a2a8"));

    kGs.insert(std::pair<int, std::string>(165, " 0"));
    xGs.insert(std::pair<int, std::string>(165, " 6773fd677c52e0640394110a46dc85df7c133f8dd4a28e661899ca5d82fd545c"));
    yGs.insert(std::pair<int, std::string>(165, " 444eb6d8cd97652f0f0f25c9dd2b246bead780f5a1c6cf98e8c7f034947eb1ae"));

    kGs.insert(std::pair<int, std::string>(166, " 0"));
    xGs.insert(std::pair<int, std::string>(166, " e0f86d94d17ce565237c79aace0c87c20374e43810468050373c616b0b86f021"));
    yGs.insert(std::pair<int, std::string>(166, " c571c73730abcf47a91e832f1c89a2c9a80bcc0115fc45b3b6b79ccb5bf325a"));

    kGs.insert(std::pair<int, std::string>(167, " 0"));
    xGs.insert(std::pair<int, std::string>(167, " 42ca15ab9f245041ce991e193d696f4f4c277df908cad6038ad0772c02da6e03"));
    yGs.insert(std::pair<int, std::string>(167, " 68d2ef26c81c57c9647ce4d1fcb800eed66e85a68106bea7836889fa8c347793"));

    kGs.insert(std::pair<int, std::string>(168, " 0"));
    xGs.insert(std::pair<int, std::string>(168, " a576df8e23a08411421439a4518da31880cef0fba7d4df12b1a6973eecb94266"));
    yGs.insert(std::pair<int, std::string>(168, " 40a6bf20e76640b2c92b97afe58cd82c432e10a7f514d9f3ee8be11ae1b28ec8"));

    kGs.insert(std::pair<int, std::string>(169, " 0"));
    xGs.insert(std::pair<int, std::string>(169, " 9e5dcc62ef3b5a3b546520867be71bae6f3ba063c9acfb8dcec5725bda704896"));
    yGs.insert(std::pair<int, std::string>(169, " 6fedd12ddb925f3ea5fd3a2154c7612279605d186030f51248f2769dca82c835"));

    kGs.insert(std::pair<int, std::string>(170, " 0"));
    xGs.insert(std::pair<int, std::string>(170, " a7de08375b8745adf8d6e9f976f03b20e33625a05cef5833953ed58744bf7ea0"));
    yGs.insert(std::pair<int, std::string>(170, " a63d96b057ada5e52104a0b334888e9a645a47c0febc5aa2e04c05539bbcabaa"));

    kGs.insert(std::pair<int, std::string>(171, " 0"));
    xGs.insert(std::pair<int, std::string>(171, " c266658e689080c9c13c35ac01cff4cbe68065fde949e4a3a9f8fa104ad916fb"));
    yGs.insert(std::pair<int, std::string>(171, " e7e8593854e7daab0f798170b24627ab6b8fecdfeb61138856aef52ba0887814"));

    kGs.insert(std::pair<int, std::string>(172, " 0"));
    xGs.insert(std::pair<int, std::string>(172, " 7778a78c28dec3e30a05fe9629de8c38bb30d1f5cf9a3a208f763889be58ad71"));
    yGs.insert(std::pair<int, std::string>(172, " 34626d9ab5a5b22ff7098e12f2ff580087b38411ff24ac563b513fc1fd9f43ac"));

    kGs.insert(std::pair<int, std::string>(173, " 0"));
    xGs.insert(std::pair<int, std::string>(173, " e7b9796b5ca006d1632f482d7f0fe3932cf16a5ae104eea7a7ea1c251073e879"));
    yGs.insert(std::pair<int, std::string>(173, " 12b8988c19169e2fdf42102a737cc1ca9cb5bf25eda98af338e71089baa89d98"));

    kGs.insert(std::pair<int, std::string>(174, " 0"));
    xGs.insert(std::pair<int, std::string>(174, " 71bf01850876203c2c915a24be09a7365423daaf2aee919865d722bf2628f0f"));
    yGs.insert(std::pair<int, std::string>(174, " 527aa15d504dcf4ae33600bc1c084ce2098f9c6a231c80bbb57c5cbd45a1c334"));

    kGs.insert(std::pair<int, std::string>(175, " 0"));
    xGs.insert(std::pair<int, std::string>(175, " 218343acb9be56833a32e594c03c39e5b1911c8501213786f6376dfa39620e1"));
    yGs.insert(std::pair<int, std::string>(175, " bea81d48970a50beaf3f24fd602fbfc0443299a42f43c9ec5e0199f6506998b5"));

    kGs.insert(std::pair<int, std::string>(176, " 0"));
    xGs.insert(std::pair<int, std::string>(176, " 928955ee637a84463729fd30e7afd2ed5f96274e5ad7e5cb09eda9c06d903ac"));
    yGs.insert(std::pair<int, std::string>(176, " c25621003d3f42a827b78a13093a95eeac3d26efa8a8d83fc5180e935bcd091f"));

    kGs.insert(std::pair<int, std::string>(177, " 0"));
    xGs.insert(std::pair<int, std::string>(177, " 4f89bdee3771d350dad163b04cb18ad67ce5e9c55b58f0e7231047a60f59dd9e"));
    yGs.insert(std::pair<int, std::string>(177, " ca7952d5227a1f695c4baf4c043bb2471e4882506638df5c1016ae320156b049"));

    kGs.insert(std::pair<int, std::string>(178, " 0"));
    xGs.insert(std::pair<int, std::string>(178, " cb9e8304cae3c5a80c396baca2c3c4c994b668f079a245bf529c314cfff01197"));
    yGs.insert(std::pair<int, std::string>(178, " 62c7d2801eb80e6a127258cdff08891741b2d18c015e0a24c334e0763b989c1d"));

    kGs.insert(std::pair<int, std::string>(179, " 0"));
    xGs.insert(std::pair<int, std::string>(179, " e2f349b0f89c69bd3c8cf2a410730dc58e0beed47048c58c15f9ffc2508d2cc2"));
    yGs.insert(std::pair<int, std::string>(179, " 1feb2f280f82723781860aec760215ba42344be8e09cbdb37e347bd8e0d4c04f"));

    kGs.insert(std::pair<int, std::string>(180, " 0"));
    xGs.insert(std::pair<int, std::string>(180, " 85d0fef3ec6db109399064f3a0e3b2855645b4a907ad354527aae75163d82751"));
    yGs.insert(std::pair<int, std::string>(180, " 1f03648413a38c0be29d496e582cf5663e8751e96877331582c237a24eb1f962"));

    kGs.insert(std::pair<int, std::string>(181, " 0"));
    xGs.insert(std::pair<int, std::string>(181, " 6b790f4b19a4c4f4f607a6cfcd11df0468b482e009711ff756356d141d5fcade"));
    yGs.insert(std::pair<int, std::string>(181, " d03a981b2ff9eb3ef296661f9cae09cba83fa5b47be26b0ab6fff86fc338d3ff"));

    kGs.insert(std::pair<int, std::string>(182, " 0"));
    xGs.insert(std::pair<int, std::string>(182, " 41149b2c2d7ebed3c162c367acc4f8fe3d2479de85978be0bb0ccdabe3a3e0cb"));
    yGs.insert(std::pair<int, std::string>(182, " c90d5b92db7c30542b415c9b9902cf28b3ec7805ef490f2470e92e98339033a8"));

    kGs.insert(std::pair<int, std::string>(183, " 0"));
    xGs.insert(std::pair<int, std::string>(183, " d1fad4fa4e7c849dfaec3dfe2872a7ba664a9b8205c29cebf8dddd28e3f3d3fc"));
    yGs.insert(std::pair<int, std::string>(183, " 8fe19714a348fdfe5473f70e858b7818bad37131eff37326ed22343c50f3704d"));

    kGs.insert(std::pair<int, std::string>(184, " 0"));
    xGs.insert(std::pair<int, std::string>(184, " ff2b0dce97eece97c1c9b6041798b85dfdfb6d8882da20308f5404824526087e"));
    yGs.insert(std::pair<int, std::string>(184, " 493d13fef524ba188af4c4dc54d07936c7b7ed6fb90e2ceb2c951e01f0c29907"));

    kGs.insert(std::pair<int, std::string>(185, " 0"));
    xGs.insert(std::pair<int, std::string>(185, " 2982dbbc5f366c9f78e29ebbecb1bb223deb5c4ee638b4583bd3a9af3149f8ef"));
    yGs.insert(std::pair<int, std::string>(185, " a61b5be9af66220ab9fa5339c7b5bc9d095db99412e3ed8456e726b016c7a248"));

    kGs.insert(std::pair<int, std::string>(186, " 0"));
    xGs.insert(std::pair<int, std::string>(186, " 1a28e5042af0c0f6b436eb590497db5860011f4580e1765885289f612380441b"));
    yGs.insert(std::pair<int, std::string>(186, " 55779a7996c59dab7c78329a8976f0ed04b3e75b46ee67aeb05f606a8452af25"));

    kGs.insert(std::pair<int, std::string>(187, " 0"));
    xGs.insert(std::pair<int, std::string>(187, " c8b83e9535f30601d250cc0bd3f20142edd5eb7985d83242eef0e39621e30a7"));
    yGs.insert(std::pair<int, std::string>(187, " dcc7077065fdac7b850e3f17efdc854aacad237b987134dbebf7beb9ff688de"));

    kGs.insert(std::pair<int, std::string>(188, " 0"));
    xGs.insert(std::pair<int, std::string>(188, " 827fbbe4b1e880ea9ed2b2e6301b212b57f1ee148cd6dd28780e5e2cf856e241"));
    yGs.insert(std::pair<int, std::string>(188, " c60f9c923c727b0b71bef2c67d1d12687ff7a63186903166d605b68baec293ec"));

    kGs.insert(std::pair<int, std::string>(189, " 0"));
    xGs.insert(std::pair<int, std::string>(189, " b77f12a7dce56b973e2d7c8d576e6b3660470a9218b87461ef6e44b70cb1815d"));
    yGs.insert(std::pair<int, std::string>(189, " 4b6f85b14f86acc43f0cefb373cc2e654c42f0f91a44816d6ba3d2bc8e57dbc5"));

    kGs.insert(std::pair<int, std::string>(190, " 0"));
    xGs.insert(std::pair<int, std::string>(190, " 48973b943018bf1247b308b2cb79f956d858d8df4977c5970fe5dad2c45565ec"));
    yGs.insert(std::pair<int, std::string>(190, " 761f75684f3cdc1b6437bb3a01445af1511b3596580477b83b879075faed07e9"));

    kGs.insert(std::pair<int, std::string>(191, " 0"));
    xGs.insert(std::pair<int, std::string>(191, " e931258e8eb5559c6d6972728a704c170b775a265b4527d4a4d4d742bbfd71fa"));
    yGs.insert(std::pair<int, std::string>(191, " fb1e33364c3fdee0e85eb4169c954b40b3946ce1bb5e35f33d9bd0d3174d3307"));

    kGs.insert(std::pair<int, std::string>(192, " 0"));
    xGs.insert(std::pair<int, std::string>(192, " eaa649f21f51bdbae7be4ae34ce6e5217a58fdce7f47f9aa7f3b58fa2120e2b3"));
    yGs.insert(std::pair<int, std::string>(192, " be3279ed5bbbb03ac69a80f89879aa5a01a6b965f13f7e59d47a5305ba5ad93d"));

    kGs.insert(std::pair<int, std::string>(193, " 0"));
    xGs.insert(std::pair<int, std::string>(193, " 3adb9db3beb997eec2623ea5002279ea9e337b5c705f3db453dbc1cc1fc9b0a8"));
    yGs.insert(std::pair<int, std::string>(193, " 374e2d6daee74e713c774de07c095ff6aad9c8f9870266cc61ae7975f05bbdda"));

    kGs.insert(std::pair<int, std::string>(194, " 0"));
    xGs.insert(std::pair<int, std::string>(194, " 129e53ac428e9cbb7e10955e56c5fc69fefdff56963e7caf054e9e0c90ae86f9"));
    yGs.insert(std::pair<int, std::string>(194, " 415ecb958aee9a29b2da2115b712183fb2a232fd16b3e01b822efdcd1e89c85d"));

    kGs.insert(std::pair<int, std::string>(195, " 0"));
    xGs.insert(std::pair<int, std::string>(195, " 60144494c8f694485b85ecb6aee10956c756267d12894711922243d5e855b8da"));
    yGs.insert(std::pair<int, std::string>(195, " 8bb5d669f681e6469e8be1fd9132e65b543955c27e3f2a4bad500590f34e4bbd"));

    kGs.insert(std::pair<int, std::string>(196, " 0"));
    xGs.insert(std::pair<int, std::string>(196, " e4a42d43c5cf169d9391df6decf42ee541b6d8f0c9a137401e23632dda34d24f"));
    yGs.insert(std::pair<int, std::string>(196, " 4d9f92e716d1c73526fc99ccfb8ad34ce886eedfa8d8e4f13a7f7131deba9414"));

    kGs.insert(std::pair<int, std::string>(197, " 0"));
    xGs.insert(std::pair<int, std::string>(197, " fd6451fb84cfb18d3ef0acf856c4ef4d0553c562f7ae4d2a303f2ea33e8f62bb"));
    yGs.insert(std::pair<int, std::string>(197, " e745ceb2b1871578b6fe7a5c1bc344ccfa2ab492d200e83fd0ad9086132c0911"));

    kGs.insert(std::pair<int, std::string>(198, " 0"));
    xGs.insert(std::pair<int, std::string>(198, " 1eee207cb24086bc716e81a06f9edbbb0042e2d5dcf3c7a1fa1d1fb9d5fe696b"));
    yGs.insert(std::pair<int, std::string>(198, " 652cbd19aef6269cd2b196d12461c95f7a02062e0afd694ebb45670e7429337b"));

    kGs.insert(std::pair<int, std::string>(199, " 0"));
    xGs.insert(std::pair<int, std::string>(199, " cc0ea33ea8a9eb14d465ab2c346e2111e1c0fc017c57257908d40f19ef94c0d5"));
    yGs.insert(std::pair<int, std::string>(199, " f9907a3b711c8a2fb23dd203b5fbe663f6074f266113f543deabe597af452fe6"));

    kGs.insert(std::pair<int, std::string>(200, " 0"));
    xGs.insert(std::pair<int, std::string>(200, " 1ec80fef360cbdd954160fadab352b6b92b53576a88fea4947173b9d4300bf19"));
    yGs.insert(std::pair<int, std::string>(200, " aeefe93756b5340d2f3a4958a7abbf5e0146e77f6295a07b671cdc1cc107cefd"));

    kGs.insert(std::pair<int, std::string>(201, " 0"));
    xGs.insert(std::pair<int, std::string>(201, " 5be7ea3519f04bc6cbeeaa0344fc90bb8e8462f6ebd890560dae805d414ff9e4"));
    yGs.insert(std::pair<int, std::string>(201, " 32f32ec3f638e605477f890f655ab7fe0e99c6302119a3094030b07847e0bdbb"));

    kGs.insert(std::pair<int, std::string>(202, " 0"));
    xGs.insert(std::pair<int, std::string>(202, " 58f099116eae4e650813fc8698df7f5cd50028649f853991e3fb545f4ddb7bb8"));
    yGs.insert(std::pair<int, std::string>(202, " 7e07002aaffe111a0d62ff7614638066507ee4062d174302bdec73582e5b2d6e"));

    kGs.insert(std::pair<int, std::string>(203, " 0"));
    xGs.insert(std::pair<int, std::string>(203, " b0f9e4b9b29790b633bcc04fd860cb0f823d8d1a4cc1a1c1413c1606cc9a8e2c"));
    yGs.insert(std::pair<int, std::string>(203, " 49e82bf1843ade6d41cbb0b906fde3f03350cc02c171cee76c2066c4df3d0db4"));

    kGs.insert(std::pair<int, std::string>(204, " 0"));
    xGs.insert(std::pair<int, std::string>(204, " 146a778c04670c2f91b00af4680dfa8bce3490717d58ba889ddb5928366642be"));
    yGs.insert(std::pair<int, std::string>(204, " b318e0ec3354028add669827f9d4b2870aaa971d2f7e5ed1d0b297483d83efd0"));

    kGs.insert(std::pair<int, std::string>(205, " 0"));
    xGs.insert(std::pair<int, std::string>(205, " 574ef0ce8a597e24e5670b5c0bcd14cfeefc983c7ecb261911b2365579de5cac"));
    yGs.insert(std::pair<int, std::string>(205, " 9b99930281f19c73bd6ada0569b78451a260a7bef10008cae59aea6c75a4805"));

    kGs.insert(std::pair<int, std::string>(206, " 0"));
    xGs.insert(std::pair<int, std::string>(206, " d3d97e799d8bf9f85d909397b98c835d10a770c1aeff8645808c2d74260966d3"));
    yGs.insert(std::pair<int, std::string>(206, " 8ddbb46376bac95e6aaa89275d403ad3b5e48711be8dc4eebddeb850833c2e52"));

    kGs.insert(std::pair<int, std::string>(207, " 0"));
    xGs.insert(std::pair<int, std::string>(207, " b1aa653288b318987b974e782cbbee0ab2be78cf8f494c120040fb93968c6d4b"));
    yGs.insert(std::pair<int, std::string>(207, " 7ed6071c60810d712684aa8e2d63a83b100a1d909d623cc383d9e62ae891ac51"));

    kGs.insert(std::pair<int, std::string>(208, " 0"));
    xGs.insert(std::pair<int, std::string>(208, " fa50c0f61d22e5f07e3acebb1aa07b128d0012209a28b9776d76a8793180eef9"));
    yGs.insert(std::pair<int, std::string>(208, " 6b84c6922397eba9b72cd2872281a68a5e683293a57a213b38cd8d7d3f4f2811"));

    kGs.insert(std::pair<int, std::string>(209, " 0"));
    xGs.insert(std::pair<int, std::string>(209, " 63964eee619074e0780140fe02e90836e72328d2448386d459c5be23187f5048"));
    yGs.insert(std::pair<int, std::string>(209, " 3b6cfb3a6b89cf41a39ff9b1c34bfbc93d580b934dde6c84383a284d89309df8"));

    kGs.insert(std::pair<int, std::string>(210, " 0"));
    xGs.insert(std::pair<int, std::string>(210, " 5a3ce25b4d15b7e22d1469ddf0fc9f75afd7f12ad3cbda31f814ba1ebadb2a65"));
    yGs.insert(std::pair<int, std::string>(210, " 8b34125b92e05f63873a6dbfbf3f99af3ee28bc3d825fe8ed8b170cf1d327f1d"));

    kGs.insert(std::pair<int, std::string>(211, " 0"));
    xGs.insert(std::pair<int, std::string>(211, " 5ce605af98f93eda6910be34f0de41ff85dbcb6e69a8fa0016a733754a9f44d0"));
    yGs.insert(std::pair<int, std::string>(211, " 4cddcf9bec226bfe7ba56bd031c76c58ab3cb1bfa32eccc6c0d05f3489d30105"));

    kGs.insert(std::pair<int, std::string>(212, " 0"));
    xGs.insert(std::pair<int, std::string>(212, " da1d61d0ca721a11b1a5bf6b7d88e8421a288ab5d5bba5220e53d32b5f067ec2"));
    yGs.insert(std::pair<int, std::string>(212, " 8157f55a7c99306c79c0766161c91e2966a73899d279b48a655fba0f1ad836f1"));

    kGs.insert(std::pair<int, std::string>(213, " 0"));
    xGs.insert(std::pair<int, std::string>(213, " 9c7be00b4ef4c444df85d5f61dc1283a23605483e1f8e934b3c210d22cd3c369"));
    yGs.insert(std::pair<int, std::string>(213, " 9220c0de74b20d2052a26d455ce401483e31153a16769cbd29ee3feba2329515"));

    kGs.insert(std::pair<int, std::string>(214, " 0"));
    xGs.insert(std::pair<int, std::string>(214, " fcd83f42825263bb55664b238ccc49174dd06a70541178e76bcd92d7bb8c9e3"));
    yGs.insert(std::pair<int, std::string>(214, " 6c0bc1cfeac5fbced1d8232de5fdb683adbeaecdf1627bf4e86d55fbdf4aa9ad"));

    kGs.insert(std::pair<int, std::string>(215, " 0"));
    xGs.insert(std::pair<int, std::string>(215, " 7175407f1b58f010d4cda4c62511e59db7edcf28f5476d995cf39944b26b64f1"));
    yGs.insert(std::pair<int, std::string>(215, " 43b4554344e3d550f36d3401134cc86eb01fe8b774471d2a426e7efab24234d5"));

    kGs.insert(std::pair<int, std::string>(216, " 0"));
    xGs.insert(std::pair<int, std::string>(216, " a8e282ff0c9706907215ff98e8fd416615311de0446f1e062a73b0610d064e13"));
    yGs.insert(std::pair<int, std::string>(216, " 7f97355b8db81c09abfb7f3c5b2515888b679a3e50dd6bd6cef7c73111f4cc0c"));

    kGs.insert(std::pair<int, std::string>(217, " 0"));
    xGs.insert(std::pair<int, std::string>(217, " cac6f2e7e27faecbcb876f805ea66e63efbe9eaa753d67c1c15eb9ea7f7653a1"));
    yGs.insert(std::pair<int, std::string>(217, " f7d416e5e2aa6f194cdb65d9a42a345081e83ae5688103a068c10ad0fec5e556"));

    kGs.insert(std::pair<int, std::string>(218, " 0"));
    xGs.insert(std::pair<int, std::string>(218, " e6dfde46ee37d206efbc5932e58e43254ab767294238cb11cc9f4ab08624003d"));
    yGs.insert(std::pair<int, std::string>(218, " 8727b3b7be9139498f2f48f7b88f92203b1ce5ea527fd7dd7548650e2216b93b"));

    kGs.insert(std::pair<int, std::string>(219, " 0"));
    xGs.insert(std::pair<int, std::string>(219, " 3c4e089cd9a6823d66a40cfc7ac96082e250e3149cf211d3b0e1103548dce109"));
    yGs.insert(std::pair<int, std::string>(219, " 43fbbe669fe191b480757bca15764d379579e142d97fe697e2bf65923a19aeea"));

    kGs.insert(std::pair<int, std::string>(220, " 0"));
    xGs.insert(std::pair<int, std::string>(220, " 174a53b9c9a285872d39e56e6913cab15d59b1fa512508c022f382de8319497c"));
    yGs.insert(std::pair<int, std::string>(220, " ccc9dc37abfc9c1657b4155f2c47f9e6646b3a1d8cb9854383da13ac079afa73"));

    kGs.insert(std::pair<int, std::string>(221, " 0"));
    xGs.insert(std::pair<int, std::string>(221, " 20e6e2e796946bb630c7071ef1b92ea3d53d280e0e4501115f5da36f840dd273"));
    yGs.insert(std::pair<int, std::string>(221, " d3ad7afe4f1559e44a0ba1ad97874655811ec9793da8693cc07cfd15bb46b593"));

    kGs.insert(std::pair<int, std::string>(222, " 0"));
    xGs.insert(std::pair<int, std::string>(222, " 8e0ca824d7a351dba80280a07e71db7035ae68136cc24ca3e7b54f301a077674"));
    yGs.insert(std::pair<int, std::string>(222, " 4ec560759192d41dc569d24da62cf57cff60419d2f910290b84cbec12b7ed98"));

    kGs.insert(std::pair<int, std::string>(223, " 0"));
    xGs.insert(std::pair<int, std::string>(223, " f7bb50da51c982d1c5fa63553e3d66c1afdb5821a321b4afe96afc5ea8192441"));
    yGs.insert(std::pair<int, std::string>(223, " 93cc3be30334a526311bc63bdde6485db1cfdc1fbbc4c74bbc640ea1d45165ae"));

    kGs.insert(std::pair<int, std::string>(224, " 0"));
    xGs.insert(std::pair<int, std::string>(224, " 959396981943785c3d3e57edf5018cdbe039e730e4918b3d884fdff09475b7ba"));
    yGs.insert(std::pair<int, std::string>(224, " 2e7e552888c331dd8ba0386a4b9cd6849c653f64c8709385e9b8abf87524f2fd"));

    kGs.insert(std::pair<int, std::string>(225, " 0"));
    xGs.insert(std::pair<int, std::string>(225, " cbee1405ff0da7deafe32ca7dd73d95ed702226b391747c707275a940bc8f53b"));
    yGs.insert(std::pair<int, std::string>(225, " f6211f4f4e75f902b51f3e689b8294cf0d9ff4f68126f7282922e6b278c87f45"));

    kGs.insert(std::pair<int, std::string>(226, " 0"));
    xGs.insert(std::pair<int, std::string>(226, " add5bad28faaf5acdd580bfa0ba252e03de3beaefbd71b9cf377c88b14b311dd"));
    yGs.insert(std::pair<int, std::string>(226, " e9c43cf4da3dc3a5974e434f8359814f52d4e1e7669b9b8902f982f349d6c38d"));

    kGs.insert(std::pair<int, std::string>(227, " 0"));
    xGs.insert(std::pair<int, std::string>(227, " 53f2432ba81717143fa9df3dff41ced24a29b314bc5a8c96f5f6400a0d7c0979"));
    yGs.insert(std::pair<int, std::string>(227, " bd52effbc1f079b7ccd4e3e0911b07de4bd5a4f5c9e8b845f9f7e90c537b36a2"));

    kGs.insert(std::pair<int, std::string>(228, " 0"));
    xGs.insert(std::pair<int, std::string>(228, " d2a63a50ae401e56d645a1153b109a8fcca0a43d561fba2dbb51340c9d82b151"));
    yGs.insert(std::pair<int, std::string>(228, " e82d86fb6443fcb7565aee58b2948220a70f750af484ca52d4142174dcf89405"));

    kGs.insert(std::pair<int, std::string>(229, " 0"));
    xGs.insert(std::pair<int, std::string>(229, " baf183a76100525e23bc7202033725f922b9cd6b36c413497c6c4bacca72da5f"));
    yGs.insert(std::pair<int, std::string>(229, " deac9fbe9ccb4d335688bd58dd69b1d18e2336c5ca739361377ce628a8f2a0cf"));

    kGs.insert(std::pair<int, std::string>(230, " 0"));
    xGs.insert(std::pair<int, std::string>(230, " f7aef8a7e38440238f9332906e48f6fd5adbd02d56b76a5ffa5aca58c56c3943"));
    yGs.insert(std::pair<int, std::string>(230, " 4e3b0b44d5ffda797c442bbdc3ab3fcfeec30184a8dcd003431f627facf442f1"));

    kGs.insert(std::pair<int, std::string>(231, " 0"));
    xGs.insert(std::pair<int, std::string>(231, " dfb547cb10019036c5a2e29f0dddbb1f7af2fa25a3c7a78c1fac945711924459"));
    yGs.insert(std::pair<int, std::string>(231, " 9accd2a9ba0f47088b8389ce9dc864cc22af0930e5c031dcfa205e0dcc65fd9e"));

    kGs.insert(std::pair<int, std::string>(232, " 0"));
    xGs.insert(std::pair<int, std::string>(232, " 64587e2335471eb890ee7896d7cfdc866bacbdbd3839317b3436f9b45617e073"));
    yGs.insert(std::pair<int, std::string>(232, " d99fcdd5bf6902e2ae96dd6447c299a185b90a39133aeab358299e5e9faf6589"));

    kGs.insert(std::pair<int, std::string>(233, " 0"));
    xGs.insert(std::pair<int, std::string>(233, " b866d6b142df940f2cf28b54c92f0c1294e0b6a22a91f2ef44bcd88c4384480d"));
    yGs.insert(std::pair<int, std::string>(233, " 1914b0b3426aeb7089a278d7ea9ad7ac24e522804b1d86d60e659b470c4cafa8"));

    kGs.insert(std::pair<int, std::string>(234, " 0"));
    xGs.insert(std::pair<int, std::string>(234, " ec2bb89085de819ec4d9d1646102ba87e2d52ae4ed4fe455d229cda81db20d6c"));
    yGs.insert(std::pair<int, std::string>(234, " ccecc17661e013a1332f66f0650940c633a2364be87efa98a0e99c4d629cf4a0"));

    kGs.insert(std::pair<int, std::string>(235, " 0"));
    xGs.insert(std::pair<int, std::string>(235, " 71c4a7e389e296ced39d75ef5e545905e50050640f50becf38a60ecb23b09d0f"));
    yGs.insert(std::pair<int, std::string>(235, " 1313fadb737af3ba0af3e0a292f810aa786f2b084a62ffc7637b1f01720ddb62"));

    kGs.insert(std::pair<int, std::string>(236, " 0"));
    xGs.insert(std::pair<int, std::string>(236, " 8481bde0e4e4d885b3a546d3e549de042f0aa6cea250e7fd358d6c86dd45e458"));
    yGs.insert(std::pair<int, std::string>(236, " 38ee7b8cba5404dd84a25bf39cecb2ca900a79c42b262e556d64b1b59779057e"));

    kGs.insert(std::pair<int, std::string>(237, " 0"));
    xGs.insert(std::pair<int, std::string>(237, " 9629a450bd383a8b9fd43c6cd1d492bf392ed605299561dde54433526ce9f114"));
    yGs.insert(std::pair<int, std::string>(237, " bf439b280c5fb6d7576befd220cef64db925593e5c56af8dca3972c4a24aa391"));

    kGs.insert(std::pair<int, std::string>(238, " 0"));
    xGs.insert(std::pair<int, std::string>(238, " b73b1c47ef1e4688eb1730da7cc893df1477d747e187e18383d38d9626ca6cc3"));
    yGs.insert(std::pair<int, std::string>(238, " 584315cb294922a90a57d64bbcc805097322a25209757f5afac35d76a54fdba3"));

    kGs.insert(std::pair<int, std::string>(239, " 0"));
    xGs.insert(std::pair<int, std::string>(239, " edfe16b2db40180311f9892007a2fef7d05b2a3bb676899f9c6e2192d38f93e0"));
    yGs.insert(std::pair<int, std::string>(239, " ee6902f1fca5db3694d74faa4b05d0d25b3d5100c46e227e3d01793de29405ad"));

    kGs.insert(std::pair<int, std::string>(240, " 0"));
    xGs.insert(std::pair<int, std::string>(240, " 13464a57a78102aa62b6979ae817f4637ffcfed3c4b1ce30bcd6303f6caf666b"));
    yGs.insert(std::pair<int, std::string>(240, " 69be159004614580ef7e433453ccb0ca48f300a81d0942e13f495a907f6ecc27"));

    kGs.insert(std::pair<int, std::string>(241, " 0"));
    xGs.insert(std::pair<int, std::string>(241, " eb3cf8f532245362ec05c88c85fe12d19182be7dceabe577c75849c6065084ae"));
    yGs.insert(std::pair<int, std::string>(241, " c833c78222d9d70043fe63dcefdca4a1f52b45c5e7dbd2a66f67c1fff96b9480"));

    kGs.insert(std::pair<int, std::string>(242, " 0"));
    xGs.insert(std::pair<int, std::string>(242, " bdf1a67d092d99974f7a60f2184519b2a576fcf984a201d9f8e5bcbcc2e9a5d0"));
    yGs.insert(std::pair<int, std::string>(242, " 4095902bab65a1aaa80be54a86bf7baaa6280b61e5626461cdb4f7018562ff7b"));

    kGs.insert(std::pair<int, std::string>(243, " 0"));
    xGs.insert(std::pair<int, std::string>(243, " 68856a6eddc4ec29cd5be267b64483b48c3b4196477da62abde5fc173b27e771"));
    yGs.insert(std::pair<int, std::string>(243, " 77a33df14f79a1fb13b6fd49c19f7b4a331d22f293b0733a6118d62a07bbdab6"));

    kGs.insert(std::pair<int, std::string>(244, " 0"));
    xGs.insert(std::pair<int, std::string>(244, " bc4a9df5b713fe2e9aef430bcc1dc97a0cd9ccede2f28588cada3a0d2d83f366"));
    yGs.insert(std::pair<int, std::string>(244, " d3a81ca6e785c06383937adf4b798caa6e8a9fbfa547b16d758d666581f33c1"));

    kGs.insert(std::pair<int, std::string>(245, " 0"));
    xGs.insert(std::pair<int, std::string>(245, " da433d5e11ceccc0abc5c7626ce7bab42e89b221f785c409282de545f3fceb19"));
    yGs.insert(std::pair<int, std::string>(245, " e498dbd321a810301debbdc4af95e5218e77fc2d9227b277684e7120a6f5cc64"));

    kGs.insert(std::pair<int, std::string>(246, " 0"));
    xGs.insert(std::pair<int, std::string>(246, " 31e8e1ee9e8c7ec1c1c116981c16efdbcc4838a72207e0654de275c5acf692a"));
    yGs.insert(std::pair<int, std::string>(246, " ad7e7f5b465b353dd9d0970290d6743b70649827c5bf73b09cc2a84eb16f667a"));

    kGs.insert(std::pair<int, std::string>(247, " 0"));
    xGs.insert(std::pair<int, std::string>(247, " a9878607a88d61155d3e00d862657f73e9c9bf363fc7a91592bbd7ff81f488b6"));
    yGs.insert(std::pair<int, std::string>(247, " d181a1abd58895d61c063e7c82157c2239d0f01964ad5c6d495a7bbb031dab1d"));

    kGs.insert(std::pair<int, std::string>(248, " 0"));
    xGs.insert(std::pair<int, std::string>(248, " 8c28a97bf8298bc0d23d8c749452a32e694b65e30a9472a3954ab30fe5324caa"));
    yGs.insert(std::pair<int, std::string>(248, " 40a30463a3305193378fedf31f7cc0eb7ae784f0451cb9459e71dc73cbef9482"));

    kGs.insert(std::pair<int, std::string>(249, " 0"));
    xGs.insert(std::pair<int, std::string>(249, " ab1ac1872a38a2f196bed5a6047f0da2c8130fe8de49fc4d5dfb201f7611d8e2"));
    yGs.insert(std::pair<int, std::string>(249, " 13f4a37a324d17a1e9aa5f39db6a42b6f7ef93d33e1e545f01a581f3c429d15b"));

    kGs.insert(std::pair<int, std::string>(250, " 0"));
    xGs.insert(std::pair<int, std::string>(250, " 2564fe9b5beef82d3703a607253f31ef8ea1b365772df434226aee642651b3fa"));
    yGs.insert(std::pair<int, std::string>(250, " 8ad9f7a60678389095fa14ae1203925f14f37dab6b79816edb82e6a301e5122d"));

    kGs.insert(std::pair<int, std::string>(251, " 0"));
    xGs.insert(std::pair<int, std::string>(251, " ff3d6136ffac5b0cbfc6c5c0c30dc01a7ea3d56c20bd3103b178e3d3ae180068"));
    yGs.insert(std::pair<int, std::string>(251, " 133239be84e4000e40d0372cdd96adc1547676f24001f5e670a6bb6e188c6077"));

    kGs.insert(std::pair<int, std::string>(252, " 0"));
    xGs.insert(std::pair<int, std::string>(252, " 8ea9666139527a8c1dd94ce4f071fd23c8b350c5a4bb33748c4ba111faccae0"));
    yGs.insert(std::pair<int, std::string>(252, " 620efabbc8ee2782e24e7c0cfb95c5d735b783be9cf0f8e955af34a30e62b945"));

    kGs.insert(std::pair<int, std::string>(253, " 0"));
    xGs.insert(std::pair<int, std::string>(253, " c25f637176220cd9f3a66df315559d8263cf2a23a4ab5ab9a293131da190b632"));
    yGs.insert(std::pair<int, std::string>(253, " 53154fede94d2873989049903809d7980a9f04ff9e027a1d6eebf3d6fc9590cf"));

    kGs.insert(std::pair<int, std::string>(254, " 0"));
    xGs.insert(std::pair<int, std::string>(254, " 2a9e8dfe3cce6bab3e82d82a5688544c0c7b55dc31978b4de2ccb3b7d466d561"));
    yGs.insert(std::pair<int, std::string>(254, " 1dfeda5c16e651fbac7b5ad608b96cf5e01eaec17a02182f96ccf5252e76373"));

    kGs.insert(std::pair<int, std::string>(255, " 0"));
    xGs.insert(std::pair<int, std::string>(255, " b23790a42be63e1b251ad6c94fdef07271ec0aada31db6c3e8bd32043f8be384"));
    yGs.insert(std::pair<int, std::string>(255, " fc6b694919d55edbe8d50f88aa81f94517f004f4149ecb58d10a473deb19880e"));

    return 0;
}

#endif /// SECP256K1_SANDBOX_POINT_CPP