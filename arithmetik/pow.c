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
