/*#include "jui.h"
#include "style.h"
#include "lcd/lcd.h"
#include <stdlib.h>
#include "fatfs/ff.h"
#include "imagecomponent.h"

void image_draw_callback(component_t* component, rectangle_t rect);

void image_create(component_t* image style_t style, char* name) {
    image->flags = 0;
    image->draw_func = image_draw_callback;
    image->selected_func = NULL;
    image->style = style;
    image->contents = name;
}

void image_draw_callback(component_t* component, rectangle_t rect) {
    style_draw(rect, component->style);

    init_pix_stream(rect);
    unsigned int read = 0;
    uint16_t buffer[F_CHUNK_READ_SIZE];
    do {
        FRESULT result = f_read(component->contents, buffer, F_CHUNK_READ_SIZE * 2, &read);

        if (result == FR_OK) {
        char c[] = {read / 10 + 48, read % 10 + 48, '\n', '\0'};
        display_string("Read: ");
        display_string(c);

        pix_stream(buffer, read / 2);
        } else {
        char c[] = {result + 48, '\n', '\0'};
        display_string("File read error: ");
        display_string(c);
        }
    } while (read == F_CHUNK_READ_SIZE * 2);
}*/