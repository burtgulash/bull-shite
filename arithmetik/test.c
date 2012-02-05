#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned divide2(unsigned a, unsigned b);
unsigned divide(unsigned a, unsigned b);

int main()
{
    int i, a, b, c;

    srand(1337);
    for (i = 0; i < 1000000000; i++) {
        b = rand() + 1;
        a = rand() + 1;
        // printf("%d / %d = %d, %d, %d\n", a, b, a/b, divide(a, b), divide2(a,b));
        assert (a / b == divide(a, b));
        assert (a / b == divide2(a, b));
    }

    return 0;
}
