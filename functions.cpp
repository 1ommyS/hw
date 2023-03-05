#include "/usr/local/include/bits/stdc++.h"
#include "functions.h"

void write(char *pointer, int &byte, int &byte_size, int &index, int value, int value_size) {
    if (8 - byte_size <= value_size) {
        byte = byte << (8 - byte_size);
        int nvalue = value >> (value_size - (8 - byte_size));
        byte += nvalue;
        *(pointer + index) = byte;
        index++;
        byte = (value << (16 - value_size - byte_size)) >> (16 - value_size - byte_size);
        byte_size = value_size - (8 - byte_size);
    } else {
        byte = byte << value_size;
        byte += value;
        byte_size += value_size;
    }
}

unsigned char read(unsigned char *pointer, int &index, int &byte_size, int value_size) {
    unsigned char value = 0,
            byte = *(pointer + index);

    if (byte_size < value_size) {
        value = byte - (byte >> byte_size) * pow(2, byte_size);
        index++;
        value = value << (value_size - byte_size);
        byte = *(pointer + index);
        value_size -= byte_size;
        byte_size = 8;
    }

    value += (byte >> (byte_size - value_size)) - (byte >> byte_size) * pow(2, value_size);
    byte_size = byte_size - value_size;

    return value;
}