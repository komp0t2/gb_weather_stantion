#ifndef _PARAM_STORE_H
#define _PARAM_STORE_H
#include "inttypes.h"
typedef struct 
{
    uint16_t temp;
    uint16_t light;
}param_station_t;
uint8_t param_station_set(param_station_t *param_get);
uint8_t param_station_get(param_station_t *param_ret);
#endif