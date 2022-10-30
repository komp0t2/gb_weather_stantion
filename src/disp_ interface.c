#include "TFT.h"
typedef struct item item;
typedef struct tab tab;
void draw_tab(tab *draw_tab);
void draw_button();
struct item
{
    tab *parent;
    tab *child;
    item *prev;
    item *next;
    uint8_t x;
    uint8_t y;
    void (*draw)(item *draw_item);
    void (*select)();
    const char text[16];
};
struct tab
{
    item *first;
    item *select;
    void (*draw)();
};
item null_item = {0, 0, 0, 0, 0, 0, 0, 0, ""};
tab null_tab = {0,0,0};
#define MENU_ITEM(name,parent, child, prev, next, x, y, draw, select, text)\
extern tab parent;\
extern tab child;\
extern item prev;\
extern item next;\
item name = {&parent, &child, &prev, &next, x, y, draw, select, text}
#define MENU_TAB(name,first,select, draw)\
extern item first;\
extern item select;\
tab name = {&first, &select, draw}

/********************************************************************************/
/*********************************CREATE MENU************************************/
/********************************************************************************/
MENU_TAB(main_tab,temp,temp,0);
MENU_ITEM(temp, main_tab, null_tab, light, light, 10, 20, temp_btn_draw, 0, "Temp");
MENU_ITEM(light, main_tab, null_tab, light, temp, 10, 50, light_btn_draw, 0, "Light");
/********************************************************************************/
/********************************************************************************/
tab *current_tab = &main_tab;
TFT *display;
void disp_init()
{
    display = TFT_Create();
    TFT_Begin(display);
    TFT_Background(display, TFT_COLOR_BLACK);
    draw_tab(&main_tab);
}
void draw_tab(tab *draw_tab)
{
    item *current_item = draw_tab->first;
    current_item->draw(current_item);
    while(current_item->next != &null_item)
    {
        current_item = current_item->next;
        if(current_item->draw != 0)
        {
            current_item->draw(current_item);
        }
    }
}
void draw_button(item *draw_item)
{
    TFT_drawRect(display, draw_item->x, draw_item->y, 50, 10, TFT_COLOR_WHITE);
    TFT_drawText(display, draw_item->x + 25, draw_item->y + 5, draw_item->text);
}
void temp_btn_draw(item *draw_item)
{
    
}