#include "SamplingControl.h"

void SamplingControl_init(SamplingControl *config) { // 100011
    config->USB_NORMAL = 0;
    config->BOSR       = 0;
    config->SR         = 0x00;
    config->CLKIDIV2   = 0;
    config->CLKODIV2   = 0;
}

unsigned int SamplingControl_build(SamplingControl *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->USB_NORMAL << offset; offset += 1;
    temp |= config->BOSR       << offset; offset += 1;
    temp |= config->SR         << offset; offset += 4;
    temp |= config->CLKIDIV2   << offset; offset += 1;
    temp |= config->CLKODIV2   << offset;

    return temp;
}
