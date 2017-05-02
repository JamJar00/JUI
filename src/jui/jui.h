#ifndef jui_jui_h
#define jui_jui_h

#include "style.h"

#include "lcd/lcd.h"
#include "fatfs/ff.h"
#include "lcd/svgrgb565.h"

#define SELECT_LINE_COLOUR GREY
#define SELECT_LINE_OFFSET 4
#define SELECT_LINE_THICKNESS 2

/* #define F_CHUNK_READ_SIZE 10 */
FATFS FatFs;

typedef struct component_t {
    uint8_t flags;
    void (*draw_func) (struct component_t* component, rectangle_t rect);
    void (*selected_func) (struct component_t* component);
    style_t style;
    void* contents;
} component_t;

#define COMPONENT_SELECTABLE 1

void init_jui();

#endif