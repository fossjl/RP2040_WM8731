#include "LineInConfig.h"

void LineInConfig_init(LineInConfig *config) {
    config->INVOL  = 0x17;
    config->INMUTE = 1;
    config->INBOTH = 0;
}

unsigned int LineInConfig_build(LineInConfig *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->INVOL   << offset; offset += 5;
    offset += 2; // Unused bits
    temp |= config->INMUTE  << offset; offset += 1;
    temp |= config->INBOTH  << offset;

    return temp;
}

