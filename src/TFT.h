/* Copyright (c) 2013, Enrico Gueli <enrico.gueli@gmail.com> All
rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _ARDUINO_TFT_H
#define _ARDUINO_TFT_H
#define TFT_CS 10
#define TFT_RS 9
#define TFT_RST 8
#define TFT_COLOR_BLACK 0x0
#define TFT_COLOR_WHITE 0xFFFF
#ifdef __cplusplus
#include "Arduino.h"
#include "utility/Adafruit_GFX.h"
#include "utility/Adafruit_ST7735.h"
/// The Arduino LCD is a ST7735-based device.
/// By default, it is mounted horizontally.
/// TFT class follows the convention of other
/// Arduino library classes by adding a begin() method
/// to be called in the setup() routine.
/// @author Enrico Gueli <enrico.gueli@gmail.com>
class TFT : public Adafruit_ST7735 {
public:
  TFT(uint8_t CS, uint8_t RS, uint8_t RST);

  void begin();  
};
TFT screen = TFT(TFT_CS, TFT_RS, TFT_RST);
/// Esplora boards have hard-wired connections with
/// the Arduino LCD if mounted on the onboard connector.
#if ARDUINO_AVR_ESPLORA // are we building for Esplora?
extern TFT EsploraTFT;
#endif
#else
typedef struct TFT TFT;
typedef uint16_t TFT_color_t;
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "inttypes.h"
TFT* TFT_Create();
void TFT_Begin(TFT*);
void TFT_Background(TFT* scr, uint16_t color);
void TFT_drawRect(TFT* scr, uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint16_t color);
void TFT_drawText(TFT* scr, uint8_t x0, uint8_t y0, const char *text);
void TFT_drawBitmap(TFT* scr, uint8_t x0, uint8_t y0, const uint8_t *bitmap, uint8_t w, uint8_t h, uint16_t color);
void TFT_setTextSize(TFT *scr, uint8_t size);
void TFT_stroke(TFT *scr, uint16_t color);
#ifdef __cplusplus
}
#endif
#endif // _ARDUINO_TFT_H

