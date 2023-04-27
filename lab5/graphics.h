#include <lcom/lcf.h>
#include <stdint.h>
#include "vbe.h"

int (set_graphics_mode)(uint16_t submode);

int (map_phys_mem)(uint16_t mode);

int (pixel_index)(uint16_t x, uint16_t y, uint16_t BytesPerPixel);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

uint32_t (get_color)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles);
