#include "Arduino.h"
#include "disp_interface.h"
#include "param_store.h"
void setup()
{
    pinMode(4, OUTPUT);
    disp_init();
}
param_station_t local_param_buf;
void loop()
{
    disp_update();
    local_param_buf.light++;
    if(param_station_set(&local_param_buf))
    {
        digitalWrite(4, !digitalRead(4));
    }
    delay(100);
}