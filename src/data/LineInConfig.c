#include "LineInConfig.h"

void LineInConfig_init(LineInConfig *config) {
    config->INVOL = 0x17;
    config->INMUTE = 1;
    config->INBOTH = 0;
}

unsigned int LineInConfig_build(LineInConfig *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->INVOL   << offset; offset += 5;
    temp |= config->INMUTE  << offset; offset += 1;
    temp |= config->INBOTH  << offset; offset += 8;

    return temp;
}

