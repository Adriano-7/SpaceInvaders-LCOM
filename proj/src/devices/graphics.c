#include "graphics.h"

struct minix_mem_range mem_range;
vbe_mode_info_t mode_info;
uint8_t* video_mem;
uint16_t BytesPerPixel;

int (set_graphics_mode)(uint16_t submode) {
  reg86_t reg;
  memset(&reg, 0, sizeof(reg));	

  reg.intno = GR_INTNO; //I want to access the video part of the bios
  reg.ah = GR_AH; //Command regarding the VBE
  reg.al = GR_AL; //Change the mode

  reg.bx = GR_BX(submode);

  if(sys_int86(&reg)) {printf("Error writhing the vbe command to change to graphics mode \n"); return 1;}

  return 0;
}

int map_phys_mem(uint16_t mode){

  memset(&mode_info, 0, sizeof(mode_info));
  if(vbe_get_mode_info(mode, &mode_info)) return 1;

  BytesPerPixel = (mode_info.BitsPerPixel+7)/8;

  unsigned int vram_base = mode_info.PhysBasePtr;
  unsigned int vram_size = mode_info.XResolution*mode_info.YResolution*BytesPerPixel;

  mem_range.mr_base = vram_base;
  mem_range.mr_limit = vram_base + vram_size;

  if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem_range)) {printf("Error obtaining permission to access physical memory\n"); return 1;}

  video_mem = vm_map_phys(SELF, (void *)mem_range.mr_base, vram_size);
  if(video_mem == MAP_FAILED) {printf("Error mapping video memory\n"); return 1;}

  return 0;
}

uint32_t (correctColor) (uint32_t color){
  if(mode_info.BitsPerPixel == 32){
    return color;
  }
  return color & ((1 << mode_info.BitsPerPixel) -1);
}

int (pixel_index)(uint16_t x, uint16_t y){
  return (y*mode_info.XResolution + x) * BytesPerPixel;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
  if(memcpy(&video_mem[pixel_index(x, y)], &color, BytesPerPixel) == NULL){
    printf("Error drawing the pixel\n");
    return 1;
  }
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(unsigned i=0; i<len; i++){
    if(vg_draw_pixel(x+i, y, color)) {printf("Error drawing pixel (%d, %d)\n", x+i, y); return 1;}
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(unsigned j=0; j<height; j++){
    if(vg_draw_hline(x, y+j, width, color)) {printf("Error drawing line %d\n", j); return 1;}
  }
  return 0;
}

uint32_t (color_indexed)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles){
  return (first + (row*no_rectangles+col)*step) % (1<<mode_info.BitsPerPixel);
}

uint32_t (color_direct)(uint16_t row, uint16_t col, uint8_t step, uint32_t first){

  uint32_t R_First = (first >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize)-1);
  uint32_t G_First = (first >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize)-1);
  uint32_t B_First = (first >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize)-1);

  uint32_t R = (R_First + col * step) % (1 << mode_info.RedMaskSize);
  uint32_t G = (G_First + row * step) % (1 << mode_info.GreenMaskSize);
  uint32_t B = (B_First + (col+row)*step) % (1 << mode_info.BlueMaskSize);

  return (R << mode_info.RedFieldPosition) | (G << mode_info.GreenFieldPosition) | (B << mode_info.BlueFieldPosition);
}

uint32_t (get_color)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles){
  if(mode_info.MemoryModel == DIRECT_COLOR_MODE) return color_direct(row, col, step, first);
  return color_indexed(row, col, step, first, no_rectangles);
}

int vg_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step){
  uint16_t height = mode_info.YResolution/no_rectangles;
  uint16_t width = mode_info.XResolution/no_rectangles;

  for(int i=0; i<no_rectangles; i++){
    for(int j=0; j<no_rectangles; j++){
      uint32_t color = get_color(i, j, step, first, no_rectangles);
      color = correctColor(color);
      if(vg_draw_rectangle(width*j, height*i, width, height, color)) {printf("Error drawing rectangle (%d, %d)\n", i, j); return 1;}
    }
  }

  return 0;
}

int (draw_xpm)(xpm_image_t img, uint8_t* img_colors, uint16_t x, uint16_t y){

  if(img_colors==NULL) return 1;

  for(int i=0; i<img.height; i++){
    for(int j=0; j<img.width; j++){
      if(vg_draw_pixel(x+j, y+i, *img_colors++)) {printf("Error drawing pixel (%d, %d) of the xpm\n", x+j, y+i); return 1;}
    }
  }

  return 0;
}

int (erase_screen)(){
  if(vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 20)) {printf("Error erasing screen\n"); return 1;}
  return 0;
}

bool pos_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed){
  if(verticalMovement){
    if(positiveMovement) *y = (*y+speed > yf) ? yf : *y+speed;
    else *y = (*y-speed < yf) ? yf : *y-speed;
    return true;
  }

  if(positiveMovement) *x = (*x+speed > xf) ? xf : *x+speed;
  else *x = (*x-speed < xf) ? xf : *x-speed;
  return true;
}

bool neg_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int* frameCounter){
  *frameCounter = *frameCounter + 1;
  if(*frameCounter % abs(speed) == 0){
    if(verticalMovement){
      if(positiveMovement) *y = (*y+1 > yf) ? yf : *y+1;
      else *y = (*y-1 < yf) ? yf : *y-1;
      return true;
    }
    if(positiveMovement) *x = (*x+1 > xf) ? xf : *x+1;
    else *x = (*x-1 < xf) ? xf : *x-1;
    return true;
  }
  return false;
}

bool coordinates_update(uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int* frameCounter, bool verticalMovement, bool positiveMovement){
  if(speed>0) return pos_speed_update(verticalMovement, positiveMovement, x, y, xf, yf, speed);
  return neg_speed_update(verticalMovement, positiveMovement, x, y, xf, yf, speed, frameCounter);
}
