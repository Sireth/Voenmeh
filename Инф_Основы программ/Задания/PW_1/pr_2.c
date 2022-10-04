#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main()
{
    char c;
    unsigned char uc;
    int i;
    unsigned u;
    short s;
    long l;
    printf("sizeof(i)=%d\tsizeof(u)=%d\tsizeof(s)=%d\tsizeof(l)=%d\n\n",
          sizeof(i), sizeof(u), sizeof(s), sizeof(l));
    c = s = SHRT_MAX;
    uc = s;
    printf("SHRT_MAX : c=%d uc=%d s=%d\n", c, uc, s);
    s = s + 1;
    printf("SHRT_MAX+1 : s=%d\n", s);
    c = s; uc = s;
    printf("%d : c=%d uc=%d\n", SHRT_MIN, c, uc);
    s = 0; c = s; uc = s;
    printf("0 : c=%d uc=%d s=%d\n", c, uc, s);
    i = INT_MAX;
    l = i; u = i;
    printf("INT_MAX : i=%d u=%u l=%ld\n", i, u, l);
    i = i + 1; l = l + 1; u = u + 1;
    printf("INT_MAX+1 : i=%d u=%u l=%ld\n", i, u, l);
    i = INT_MIN;
    l = i; u = i;
    printf("INT_MIN : i=%d u=%u l=%ld\n", i, u, l);
    u = UINT_MAX;
    i = u; l = u;
    printf("UINT_MAX : i=%d u=%u l=%ld\n", i, u, l);
    u = i = -5;
    printf("-5 : i=%d u=%u\n", i, u);
    i = -5; u = 5;
    printf("int and unsigned int -5>5 : %d\n", i > u);
    c = -5; u = 5;
    printf("char and unsigned int -5>5 : %d\n\n", c > u);
    i = 5.1;
    printf("i=5.1 : i=%d\n", i);
    i = 5.9;
    printf("i=5.9 : i=%d\n", i);
    return 0;
}
