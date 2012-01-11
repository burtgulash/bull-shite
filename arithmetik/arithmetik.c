#include <signal.h>

int mula(int a, int b)
{
    int c = 0;
    while (b) {
        c += a & ~((b & 1) - 1);
        a <<= 1;
        b = (unsigned int) b >> 1;
    }
    return c;
}

int powa(int a, int b)
{
    int c = 1;
    while (b) {
        if (b & 1)
            c *= a;
        a *= a;
        b >>= 1;
    }
    return c;
}

int diva(int a, int b)
{
    int q = 0;                  // quotient
    int s = 0;                  // shift of b

    // Handle division by zero. Kill this program by floating point error.
    if (b == 0)
        raise(SIGFPE);

    // Align b with a.
    while (b < a) {
        b <<= 1;
        s++;
    }

    // Repeat while shifted b is more than or equal to original b.
    while (s >= 0) {
        if (a >= b) {
            q |= 1 << s;
            a -= b;
        } else {
            s--;
            b >>= 1;
        }
    }

    // a holds remainder, q is quotient
    return q;
}
