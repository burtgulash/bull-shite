#include <stdio.h>
#include <assert.h>

int divide2(int a, int b);
int divide(int a, int b);

int main()
{
    int i, a, b, c;

    b = (~0) >> 2;
    for (i = 1; i < 100000000; i++)
        c = divide(a, i);
        // c = a / b;

    return 0;
}
