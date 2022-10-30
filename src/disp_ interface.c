#include "disp_interface.h"
#include "disp_icon.h"
#include "TFT.h"
#include "Arduino.h"
#include "param_store.h"
#include <stdio.h>
typedef struct item_t item_t;
typedef struct tab_t tab_t;
void draw_tab(tab_t *draw_tab);
void temp_draw(item_t *draw_item);
void light_draw(item_t *draw_item);
void light_update(item_t *draw_item);
void draw_button();
struct item_t
{
    tab_t *parent;
    tab_t *child;
    item_t *prev;
    item_t *next;
    uint8_t x;
    uint8_t y;
    void (*draw)(item_t *draw_item);
    void (*select)(item_t *draw_item);
    void (*update)(item_t *draw_item);
    const char text[16];
};
struct tab_t
{
    item_t *first;
    item_t *select;
    void (*draw)();
};
item_t null_item = {0, 0, 0, 0, 0, 0, 0, 0, 0, ""};
tab_t null_tab = {0,0,0};
#define MENU_ITEM(name,parent, child, prev, next, x, y, draw, select, update, text)\
extern tab_t parent;\
extern tab_t child;\
extern item_t prev;\
extern item_t next;\
item_t name = {&parent, &child, &prev, &next, x, y, draw, select, update, text}
#define MENU_TAB(name,first,select, draw)\
extern item_t first;\
extern item_t select;\
tab_t name = {&first, &select, draw}

/********************************************************************************/
/*********************************CREATE MENU************************************/
/********************************************************************************/
MENU_TAB(main_tab,temp,temp,0);
MENU_ITEM(temp, main_tab, null_tab, light, light, 10, 20, temp_draw, 0, 0, "Temp");
MENU_ITEM(light, main_tab, null_tab, light, temp, 10, 50, light_draw, 0, light_update, "Light");
/********************************************************************************/
/********************************************************************************/
tab_t *tab = &main_tab;
TFT *display;
TFT_color_t background_color = TFT_COLOR_BLACK;
void disp_init()
{
    display = TFT_Create();
    TFT_Begin(display);
    TFT_Background(display, background_color);
    draw_tab(&main_tab);
}
void draw_tab(tab_t *draw_tab)
{
    item_t *item = draw_tab->first;
    while(item != &null_item)
    {
        if(item->draw != 0)
        {
            item->draw(item);
        }
        item = item->next != draw_tab->first ? item->next : &null_item;
    }
}
void draw_button(item_t *draw_item)
{
    TFT_drawRect(display, draw_item->x, draw_item->y, 50, 10, TFT_COLOR_WHITE);
    TFT_drawText(display, draw_item->x + 25, draw_item->y + 5, draw_item->text);
}
void temp_draw(item_t *draw_item)
{

}
param_station_t param;
char light_text_buf[20];
void light_draw(item_t *draw_item)
{
    TFT_drawRect(display, draw_item->x, draw_item->y, 50, 50, TFT_COLOR_WHITE);
    TFT_setTextSize(display, 2);
    TFT_stroke(display, TFT_COLOR_WHITE);
    char text_light[20] = "error light read";
    if(param_station_get(&param))
    {
        sprintf(text_light, "%d", param.light);
    }
    TFT_drawText(display, draw_item->x+10, draw_item->y+3, light_text_buf);
    TFT_drawBitmap(display, draw_item->x, draw_item->y+20,light_bitmap, light_bitmap_w, light_bitmap_h, TFT_COLOR_WHITE);
    memcpy(light_text_buf, text_light, sizeof(light_text_buf)/sizeof(light_text_buf[0]));
}
void light_update(item_t *draw_item)
{
    if(param_station_get(&param))
    {
        TFT_setTextSize(display, 2);
        TFT_stroke(display, background_color);
        TFT_drawText(display, draw_item->x+10, draw_item->y+3, light_text_buf);
        TFT_stroke(display, TFT_COLOR_WHITE);
        sprintf(light_text_buf, "%d", param.light);
        TFT_drawText(display, draw_item->x+10, draw_item->y+3, light_text_buf);
    }  
}
void disp_update()
{
    item_t *item = tab->first;
    while(item != &null_item)
    {
        if(item->update != 0)
        {
            item->update(item);
        }
        item = item->next != tab->first ? item->next : &null_item;
    }
}