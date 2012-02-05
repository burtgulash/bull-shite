int mul(int a, int b)
{
    int c = 0;
    while (b) {
        c += a & ~((b & 1) - 1);
        a <<= 1;
        b = (unsigned int) b >> 1;
    }
    return c;
}
