#include "Arduino.h"
#include "util/delay.h"
#define SCREEN_CS 10
#define SCREEN_DC 9
#define SCREEN_RST 8

#include "TFT.h"
TFT *display;
void setup()
{
    pinMode(4, OUTPUT);
    display = TFT_Create_c();
    TFT_Begin_c(display);
}
void loop()
{
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
    delay(1000);
}