#ifndef _WM8721_LineInConfig_H
#define _WM8721_LineInConfig_H

#include "wm8731_api.h"

struct LineInConfig_s  {
    unsigned INVOL      : 5; // Line Input Volume Control
    unsigned _unused    : 2; 
    unsigned INMUTE     : 1; // Line Input Mute to ADC
    unsigned INBOTH     : 1; // Simultanious Load of LINVOL/RINVOL & LINMUTE/RINMUTE
};

typedef struct LineInConfig_s LineInConfig;

void LineInConfig_init(LineInConfig *config);
unsigned int LineInConfig_build(LineInConfig *config);

static inline void LineInConfig_send_left(LineInConfig* cfg) {
  WM8731_CMD(WM8731_REG_LLINE_IN, LineInConfig_build(cfg));
}

static inline void LineInConfig_send_right(LineInConfig* cfg) {
  WM8731_CMD(WM8731_REG_RLINE_IN, LineInConfig_build(cfg));
}

#endif // LineInConfig
