#include "PowerDownControl.h"

void PowerDownControl_init(PowerDownControl *config) {
    config->LINEINPD = 1;
    config->MICPD    = 1;
    config->ADCPD    = 1;
    config->DACPD    = 1;
    config->OUTPD    = 1;
    config->OSCPD    = 0;
    config->CLKOUTPD = 0;
    config->POWEROFF = 1;
}

unsigned int PowerDownControl_build(PowerDownControl *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->LINEINPD << offset; offset += 1;
    temp |= config->MICPD    << offset; offset += 1;
    temp |= config->ADCPD    << offset; offset += 1;
    temp |= config->DACPD    << offset; offset += 1;
    temp |= config->OUTPD    << offset; offset += 1;
    temp |= config->OSCPD    << offset; offset += 1;
    temp |= config->CLKOUTPD << offset; offset += 1;
    temp |= config->POWEROFF << offset;

    return temp;
}

