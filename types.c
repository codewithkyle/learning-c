#include <stdio.h>

int main(int argc, char *argv[])
{
    char y; // 1 byte, 8 bits
    short s; // 2 bytes, 16 bits
    int i; // 4 bytes, 32 bits
    long long int l; // 8 bytes, 64 bit

    float f; // low accuracy
    double d; // higher accuracy

    // same size casting
    unsigned int x = 4;
    int sx = (int)(x); // type casting

    // down casting
    unsigned int bigx = 0xfffffefe;
    short kindabig = (short)bigx;

    // up casting
    short short2 = -1; // 0xffff
    int wasashrot = (int)short2; // 0xffffffff

    // cross casting
    float float2 = 3.14;
    int wasafloat = (int)float2;

    // pointer casting
    short *mydata = (short*)argv[1]; // casts char pointer to short pointer
}
