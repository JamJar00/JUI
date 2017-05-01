#include <avr/interrupt.h>
#include "jui/jui.h"
#include "jui/buttoncomponent.h"
#include "jui/textcomponent.h"
#include "jui/iconmenu.h"
#include "jui/listview.h"
#include "jui/gridview.h"
#include "jui/style.h"

#define COUNT 18

/*
FATFS fatFs;
*/

void icon_button_callback(component_t* component);
void list_button_callback(component_t* component);
void grid_button_callback(component_t* component);

iconmenu_t menu;

int main() {
  init_jui();

  sei();

  /*f_mount(&fatFs, "", 0);*/

  int i;
  char* text_items[COUNT] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
  component_t text_components[COUNT];
  component_t button_components[COUNT];
  for (i = 0; i < COUNT; i++) {
    text_create(text_components + i, NO_STYLE, text_items[i]);
    button_create(button_components + i, ICONMENU_BUTTON_STYLE, text_components + i, icon_button_callback);
  }

  menu = iconmenu_create(COUNT, button_components, 20, 20);

  iconmenu_draw(&menu);
  iconmenu_draw(&menu);

  iconmenu_select(&menu, 0);

  iconmenu_run(&menu);
}

void icon_button_callback(component_t* component) {
  char* text[] = {"Hello there!", "Good to see you!", "Do you like the menu?", "Click something!"};
  component_t text_components[4];
  component_t button_components[4];

  uint8_t i;
  for(i = 0; i < 4; i++) {
    text_create(text_components + i, NO_STYLE, text[i]);
    button_create(button_components + i, LISTVIEW_BUTTON_STYLE, text_components + i, list_button_callback);
  }

  listview_t view = listview_create(4, button_components);

  listview_draw(&view);

  listview_select(&view, 0);

  listview_run(&view);

  //Redraw icon menu when closed
  iconmenu_draw(&menu);
}

void list_button_callback(component_t* component) {
  char* text[] = {"BIG", "Tall", "Wide"};
  component_t text_components[3];
  component_t button_components[3];

  uint8_t i;
  for(i = 0; i < 3; i++) {
    text_create(text_components + i, NO_STYLE, text[i]);
    button_create(button_components + i, GRIDVIEW_BUTTON_STYLE, text_components + i, grid_button_callback);
  }

  gridview_component_t gv_components[] = 
  {
    gridview_place(0, 0, 2, 2, button_components + 0),
    gridview_place(2, 0, 1, 2, button_components + 1),
    gridview_place(0, 2, 3, 1, button_components + 2)
  };
  
  gridview_t view = gridview_create(3, 3, 3, gv_components);
  
  gridview_draw(&view);

  gridview_select(&view, 0);

  gridview_run(&view);
}

void grid_button_callback(component_t* component) {
  display_string("Clickkkked!");
}

/*
void draw_icon_from_file() {
  FIL file;
    FRESULT result;
    
    result = f_open(&file, "image.img", FA_READ);

    if (result == FR_OK) {
      display_string("File opened!");
      iconmenu_draw_icon(&menu, &file);

      f_close(&file);
    }
    else {
      char c[] = {result + 48, '\n', '\0'};
      display_string("File open error: ");
      display_string(&c);
    }
}*/