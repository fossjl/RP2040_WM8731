#include "DigitalPathControl.h"

void DigitalPathControl_init(DigitalPathControl *config) {
    config->ADCHPD = 0;
    config->DEEMP  = 0x00;
    config->DACMU  = 1;
    config->HPOR   = 0;
} 

unsigned int DigitalPathControl_build(DigitalPathControl *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->ADCHPD << offset; offset += 1;
    temp |= config->DEEMP  << offset; offset += 2;
    temp |= config->DACMU  << offset; offset += 1;
    temp |= config->HPOR   << offset;

    return temp;
}

