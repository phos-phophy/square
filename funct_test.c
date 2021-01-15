#include <math.h>

double
f1_test (double a)
{
    return a*a - 4;
}

double
f2_test (double a)
{
    return sqrt(a) - 1;
}

double
f3_test (double a)
{
    return exp(a+1) - 1;
}

double
zero_funct (double a)
{
    return 0;
}

double
f1_test_der (double a) 
{
    return 2 * a;
}

double
f2_test_der (double a)
{
    return 1 / sqrt(a) / 2;
}

double
f3_test_der (double a)
{
    return exp(a + 1);
}
