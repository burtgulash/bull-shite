#include <signal.h>

int divide(int a, int b)
{
    int q, s;                  // quotient, shift

    q = 0;
    s = 0;

    if (b == 0)
        raise(SIGFPE);

    // Align b with a.
    while (b <= (a >> 1)) {
        b <<= 1;
        s++;
    }

    // Repeat while shifted b is more than or equal to original b.
    while (s >= 0) {
        if (a >= b) {
            q |= 1 << s;
            a -= b;
        }
        s--;
        b >>= 1;
    }

    // a holds remainder, q is quotient
    return q;
}

int divide2(int a, int b)
{
    int q, x;

    q = 0;
    x = b;

    // Division by 0.
    if (b == 0)
        raise(SIGFPE);

    // Align a and b.
    while (x <= (a >> 1))
        x <<= 1;

    while (x >= b) {
        if (a >= x) {
            q |= 1;
            a -= x;
        }
        x >>= 1;
        q <<= 1;
    }
    q >>= 1; // Fix redundant shift.

    return q;
}
