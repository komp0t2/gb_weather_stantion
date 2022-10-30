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

#include "TFT.h"
#if ARDUINO_AVR_ESPLORA
TFT EsploraTFT(7, 0, 1);
#endif

TFT::TFT(uint8_t CS, uint8_t RS, uint8_t RST) 
  : Adafruit_ST7735(CS, RS, RST)
{
  // as we already know the orientation (landscape, therefore rotated),
  // set default width and height without need to call begin() first.
  _width = ST7735_TFTWIDTH;
  _height = ST7735_TFTHEIGHT;
}

void TFT::begin() {
initR(INITR_REDTAB);
//  initG();
  setRotation(2);
}
extern "C" TFT* TFT_Create()
{
  return &screen;
}
extern "C" void TFT_Begin(TFT* scr)
{
  scr->begin();
}
extern "C" void TFT_Background(TFT* scr, uint16_t color)
{
  scr->background(color);
}
extern "C" void TFT_drawRect(TFT* scr, uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint16_t color)
{
  scr->drawRect(x0, y0, w, h, color);
}
extern "C" void TFT_drawText(TFT* scr, uint8_t x0, uint8_t y0, const char *text)
{
  scr->setTextSize(1);
  scr->stroke(TFT_COLOR_WHITE);
  scr->text(text, x0, y0);
}
extern "C" void TFT_drawBitmap(TFT* scr, uint8_t x0, uint8_t y0, const uint8_t *bitmap, uint8_t w, uint8_t h, uint16_t color)
{
  scr->drawBitmap(x0, y0, bitmap, w, h, color);
}