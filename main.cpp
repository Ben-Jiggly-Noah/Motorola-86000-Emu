#include<stdio.h>
#include<stdlib.h>

using BYTE = unsigned char;
using WORD = unsigned short;
using LONG =unsigned long;
using STATUS = bool;

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

    BYTE read_byte(LONG address)
    {
        return RAM[address];
    }
    WORD read_word(LONG address)
    {
        return (RAM[address]<<8) | RAM[address+1];
    }
    LONG read_long(LONG address)
    {
        return ((RAM[address]<<24) | (RAM[address+1]<<16)) | ((RAM[address+2]<<8) | RAM[address+3]);
    }

    void write_byte(LONG address = 0, BYTE value = 0)
    {
        RAM[address]=value;
    }
    void write_word(LONG address = 0, WORD value = 0)
    {
        RAM[address]=value & 0xFF00;
        RAM[address+1]=value & 0x00FF;
    }
    void write_long(LONG address = 0, LONG value = 0)
    {
        RAM[address]=value & 0xFF000000;
        RAM[address+1]=value & 0x00FF0000;
        RAM[address+2]=value & 0x0000FF00;
        RAM[address+3]=value & 0x000000FF;
    }

    BYTE INS_ABCD_B(BYTE reg_ret = 0, LONG destination = 0, BYTE value = 0)
    {
        if (reg_ret==0) return reg_ret + value + X;
        else write_byte(read_byte(destination)+value);
    }
    BYTE INS_ABCD_W(BYTE reg_ret = 0, LONG destination = 0, WORD value = 0)
    {
        if (reg_ret==0) return reg_ret + value + X;
        else write_word(read_word(destination)+value);
    }
    BYTE INS_ABCD_L(BYTE reg_ret = 0, LONG destination = 0, LONG value = 0)
    {
        if (reg_ret==0) return reg_ret + value + X;
        else write_long(read_long(destination)+value);
    }
};


int main()
{
    CPU cpu;

    cpu.write_byte(NULL, 4);

    free((void*)cpu.RAM);
    cpu.RAM = NULL;
    return 0;
}
