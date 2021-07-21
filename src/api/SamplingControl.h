#ifndef _WM8721_SamplingControl_H
#define _WM8721_SamplingControl_H

#include "wm8731_api.h"

struct SamplingControl_s {
    unsigned USB_NORMAL :1; // Mode Select
    unsigned BOSR       :1; // Base Over-Sampling Rate 
    unsigned SR         :4; // ADC and DAC Sample rate control
    unsigned CLKIDIV2   :1; // Core Clock divider Select
    unsigned CLKODIV2   :1; // CLKOUT divider select
};

typedef struct SamplingControl_s SamplingControl;

void SamplingControl_init(SamplingControl *config);

unsigned int SamplingControl_build(SamplingControl *config);

static inline void SamplingControl_send(SamplingControl* cfg) {
  WM8731_CMD(WM8731_REG_SAMPLING_CTRL, SamplingControl_build(cfg));
}

#endif // SamplingControl
