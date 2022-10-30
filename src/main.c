#include "Arduino.h"
#include "disp_interface.h"
void setup()
{
    pinMode(4, OUTPUT);
    disp_init();
}
void loop()
{
    disp_update();
    delay(100);
}