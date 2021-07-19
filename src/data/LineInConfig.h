#ifndef _WM8721_LineInConfig_H
#define _WM8721_LineInConfig_H

struct LineInConfig_s  {
    unsigned INVOL      : 5; // Line Input Volume Control
    unsigned _unused    : 2; 
    unsigned INMUTE     : 1; // Line Input Mute to ADC
    unsigned INBOTH     : 1; // Simultanious Load of LINVOL/RINVOL & LINMUTE/RINMUTE
};

typedef struct LineInConfig_s LineInConfig;

void LineInConfig_init(LineInConfig *config);
unsigned int LineInConfig_build(LineInConfig *config);

#endif // LineInConfig
