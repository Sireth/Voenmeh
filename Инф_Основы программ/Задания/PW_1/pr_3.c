#include <stdlib.h>
#include <stdio.h>
#include <float.h>

int main()
{
    float f;
    double d;
    printf("sizeof(f)=%d\tsizeof(d)=%d\n\n", sizeof(f), sizeof(d));
    d = f = FLT_MAX;
    printf("FLT_MAX : f=%g d=%g\n", f, d);
    d = f = FLT_MIN;
    printf("FLT_MIN : f=%g d=%g\n", f, d);
    d = f = FLT_EPSILON;
    printf("FLT_EPSILON : f=%g d=%g\n", f, d);
    f = 12345678;
    printf("12345678 : f=%f\n", f);
    f = 123456789;
    printf("123456789 : f=%f\n", f);
    f = 1234567890;
    printf("1234567890 : f=%f\n", f);
    d = DBL_MAX;
    printf("DBL_MAX : d=%g\n", d);
    d = DBL_MIN;
    printf("DBL_MIN : d=%g\n", d);
    d = DBL_EPSILON;
    printf("DBL_EPSILON : d=%g\n", d);
    d = 1e15 + 1;
    printf("1e15+1 : d=%lf\n", d);
    d = 1e16 + 1;
    printf("1e16+1 : d=%lf\n", d);
    d = 10000 * 100000 + 1 - 4 * 250000000;
    printf("1 : d=%lf\n", d);
    d = 1e20 * 1e20 + 1000 - 1e22 * 1e18;
    printf("1000 : d=%lf\n", d);
    d = 1e20 * 1e20 - 1e22 * 1e18 + 1000;
    printf("1000 : d=%lf\n", d);
    f = d = 0.3;
    printf("0.3 : f=%.8f  d=%.17f\n", f, d);
    f = 0;
    while (f < 10)
        f += 0.2;
    printf("10 : f=%f\n", f);
    return 0;
}

