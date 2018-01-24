#include <stdio.h>

unsigned char shuffle_8bits(unsigned char x)
{
    /* unsigned char shuffle[8] =
        {0, 1, 2, 3, 4, 5, 6, 7}; NO CHANGE
        {7, 6, 5, 4, 3, 2, 1, 0}; REVERSE
        {0, 1, 2, 3, 7, 6, 5, 4}; REVERSE JUST HIGH 4 BITS
        {3, 2, 1, 0, 4, 5, 6, 7}; REVERSE JUST LOW 4 BITS
        {2, 5, 7, 0, 6, 1, 4, 3}; DO IT YOURSELF
    */

    unsigned char shuffle[8] = {7, 6, 5, 4, 3, 2, 1, 0};
    unsigned char r=0, bit;
    int i;

    for (i=0;i<8;i++){
        bit = (x >> i) & 1;
        r |= bit << shuffle[i];
    }

    return r;
}

unsigned char reverse_high4bits(unsigned char x)
{
    unsigned char h2, l2, r=0, t[4] = {0, 2, 1, 3};

    h2 = (x >> 4) & 0x03;
    h2 = t[h2];
    l2 = (x >> 6) & 0x03;
    l2 = t[l2];
    r = (h2 << 6) | (l2 << 4);

    return r;
}

void to_bits(char *ss, unsigned char x)
{
    int i;

    for (i=0;i<8;i++) {
        ss[i] = '0' + ((x >> (7-i)) & 1);
    }
    ss[i] = '\0';
}

int main(void)
{
    unsigned char d[SIZE], r[SIZE];
    char ss_d[80], ss_r[80];
    int i;

    for (i=0;i<SIZE;i++)
        d[i] = i;
    for (i=0;i<SIZE;i++)
        r[i] = shuffle_8bits(d[i]);

    for (i=0;i<SIZE;i++) {
        to_bits(ss_d, d[i]);
        to_bits(ss_r, r[i]);
        fprintf(stdout, "d[%2d]=0b%s, r[%2d]=0b%s\n", i, ss_d, i, ss_r);
    }

    return 0;
}
