#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main()
{
    char c;
    unsigned char uc;
    printf("sizeof(c)=%d\tsizeof(uc)=%d\n\n", sizeof(c),sizeof(uc));
    uc=c=CHAR_MAX;
    printf("CHAR_MAX : c=%d uc=%d\n", c, uc);
    c = c + 1; uc = uc + 1;
    printf("CHAR_MAX+1 : c=%d uc=%d\n", c, uc);
    uc = c = CHAR_MIN;
    printf("CHAR_MIN : c=%d uc=%d\n", c, uc);
    c = uc = UCHAR_MAX;
    printf("UCHAR_MAX : c=%d uc=%d\n", c, uc);
    c = c + 1; uc = uc + 1;
    printf("UCHAR_MAX+1 : c=%d uc=%d\n", c, uc);
    uc = c = -5;
    printf("-5 : c=%d uc=%d\n", c, uc);
    c = -5; uc = 5;
    printf("char and unsigned char -5>5 : %d\n\n", c>uc);
    return 0;
}
