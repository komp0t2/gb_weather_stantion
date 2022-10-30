#include "param_store.h"
static param_station_t param_station;
static uint8_t protect = 0;
uint8_t param_station_get(param_station_t *param_ret)
{
    uint8_t ret = 0;
    if(!protect)
    {
        protect = 1;
        *param_ret = param_station; 
        ret = 1;
        protect = 0;
    }
    return ret;
}
uint8_t param_station_set(param_station_t *param_get)
{
    uint8_t ret = 0;
    if(!protect)
    {
        protect = 1;
        param_station = *param_get; 
        ret = 1;
        protect = 0;
    }
    return ret;
}