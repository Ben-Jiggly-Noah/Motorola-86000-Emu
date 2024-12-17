#include<stdio.h>
#include<stdlib.h>

using BYTE = unsigned char;
using WORD = unsigned short;
using LONG = unsigned long;

struct CPU
{
    // Data / Address Registers
    LONG d0, d1, d2, d3, d4, d5, d6, d7 = 0;
    LONG a0, a1, a2, a3, a4, a5, a6 = 0;

    // System Registers
    LONG SP = 0;
    LONG PC = 0;

    // Status Register
    BYTE C : 1;
    BYTE V : 1;
    BYTE Z : 1;
    BYTE N : 1;
    BYTE X : 1;
    BYTE I: 3;
    BYTE O: 1;
    BYTE M: 1;
    BYTE S: 1;
    BYTE T: 2;

    BYTE* RAM = (BYTE*)malloc(4194304);

    
};


int main()
{
    CPU cpu;

    free((void*)cpu.RAM);
    cpu.RAM = NULL;
    return 0;
}