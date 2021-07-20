#include "AnalogPathControl.h"

void AnalogPathControl_init(AnalogPathControl *config) {
    config->MICBOOST = 0;               // 11010000
    config->MUTEMIC  = 1;
    config->INSEL    = 0;
    config->BYPASS   = 1;
    config->DACSEL   = 0;
    config->SIDETONE = 0;
    config->SIDEATT  = 0x00; 
}

unsigned int AnalogPathControl_build(AnalogPathControl *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->MICBOOST << offset; offset += 1; 
    temp |= config->MUTEMIC  << offset; offset += 1;
    temp |= config->INSEL    << offset; offset += 1;
    temp |= config->BYPASS   << offset; offset += 1;
    temp |= config->DACSEL   << offset; offset += 1;
    temp |= config->SIDETONE << offset; offset += 1;
    temp |= config->SIDEATT  << offset;

    return temp;
}

