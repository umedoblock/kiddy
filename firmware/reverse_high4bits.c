#include <stdio.h>

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
    unsigned char d[16], r[16];
    char ss_d[80], ss_r[80];
    int i;

    for (i=0;i<16;i++)
        d[i] = i << 4;
    for (i=0;i<16;i++)
        r[i] = reverse_high4bits(d[i]);

    for (i=0;i<16;i++) {
        to_bits(ss_d, d[i]);
        to_bits(ss_r, r[i]);
        fprintf(stdout, "d[%2d]=0b%s, r[%2d]=0b%s\n", i, ss_d, i, ss_r);
    }

    return 0;
}
