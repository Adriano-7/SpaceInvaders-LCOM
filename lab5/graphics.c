#include "graphics.h"

struct minix_mem_range mem_range;
vbe_mode_info_t mode_info;
uint8_t* video_mem;

int (set_graphics_mode)(uint16_t submode) {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));

  reg86.intno = 0x10; //Video Services
  reg86.ah = 0x4F; //
  reg86.al = 0x02; //Set VBE mode

  reg86.bx = BIT(14) | submode; //Bit 14: linear framebuffer

  if(sys_int86(&reg86)) {
    printf("Error calling sys_int86()!\n");
    return 1;
  }

  if(reg86.al != 0x4F) {
    printf("Function not supported\n");
    return 1;
  }
  else{
    if(reg86.ah==0x01){
      printf("Function call failed\n");
      return 1;
    }
    if(reg86.ah==0x02){
      printf("Function is not supported in current HW configuration\n");
      return 1;
    }
    if(reg86.ah==0x03){
      printf("Function is invalid in current video mode\n");
      return 1;
    }
  }

  return 0;
}

int map_phys_mem(uint16_t mode){
  memset(&mode_info, 0, sizeof(mode_info));
  if(vbe_get_mode_info(mode, &mode_info)){
    printf("Error retriving information on the input VBE mode\n");
    return 1;
  }

  int BytesPerPixel = (mode_info.BitsPerPixel+7)/8;
  int vram_size = mode_info.XResolution * mode_info.YResolution * BytesPerPixel;
  mem_range.mr_base = mode_info.PhysBasePtr;
  mem_range.mr_limit = mem_range.mr_base + vram_size;

  if(OK != sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem_range)){
    printf("Error mapping video memory\n");
    return 1;
  }
  video_mem = vm_map_phys(SELF, (void *)mem_range.mr_base, vram_size);
  if(video_mem == MAP_FAILED){
    printf("Error mapping video memory\n");
    return 1;
  }
  return 0;
}

int (pixel_index)(uint16_t x, uint16_t y, uint16_t BytesPerPixel){
  if(x>mode_info.XResolution){
    printf("X is out of bounds\n");
    return -1;
  }

  if(y>mode_info.YResolution){
    printf("Y is out of bounds\n");
    return -1;
  }

  return (y*mode_info.XResolution+x)*BytesPerPixel;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
  uint16_t BytesPerPixel = (mode_info.BitsPerPixel+7)/8;
  int index = pixel_index(x, y, BytesPerPixel);
  if(index == -1){
    printf("Error calculating the index\n");
    return 1;
  }

  if(memcpy(&video_mem[index], &color, BytesPerPixel) == NULL){
    printf("Error drawing the pixel\n");
    return 1;
  }
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(unsigned i=0; i<len; i++){
    if(vg_draw_pixel(x+i, y, color)){
      printf("Error drawing pixel with coordinates (%d, %d)\n", x+i, y);
      return 1;
    }
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(unsigned i=0; i<height; i++){
    if(vg_draw_hline(x, y+i, width, color)){
      printf("Error drawing line %d of the rectangle\n", i);
      return 1;
    }
  }
  return 0;
}

uint32_t (color_indexed)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles){
  return (first + (row*no_rectangles + col) * step) % (1 << mode_info.BitsPerPixel);
}

uint32_t (color_direct)(uint16_t row, uint16_t col, uint8_t step, uint32_t first){
  uint32_t R_First = (first >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize) - 1);
  uint32_t G_First = (first >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize) - 1);
  uint32_t B_First = (first >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize) - 1);

  uint32_t R = (R_First + col*step) % (1 << mode_info.RedMaskSize);
  uint32_t G = (G_First + row*step) % (1 << mode_info.GreenMaskSize);
  uint32_t B = (B_First + (row+col)*step) % (1 << mode_info.BlueMaskSize);

  return (R<<mode_info.RedFieldPosition) | (G<<mode_info.GreenFieldPosition) | (B<<mode_info.BlueFieldPosition);
}

uint32_t (get_color)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles){
  if(mode_info.MemoryModel==DIRECT_COLOR_MODE){
    return color_direct(row, col, step, first);
  }
  return color_indexed(row, col, step, first, no_rectangles);
}

int vg_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step){
  uint16_t width = mode_info.XResolution / no_rectangles;
  uint16_t height = mode_info.YResolution / no_rectangles;

  for(unsigned row=0; row<no_rectangles; row++){
    for(unsigned col=0; col<no_rectangles; col++){
      uint32_t color = get_color(row, col, step, first, no_rectangles);
      if(vg_draw_rectangle(col*width, row*height, width, height, color)){
        printf("Error drawing rectangle\n");
        return 1;
      }
    }
  }
  return 0;
}

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y){
  xpm_image_t img;
  uint8_t *sprite = xpm_load(xpm, XPM_INDEXED, &img);
  if(sprite == NULL){
    printf("Error loading sprite\n");
    return 1;
  }

  for(unsigned i=0; i<img.height; i++){
    for(unsigned j=0; j<img.width; j++){
      if(vg_draw_pixel(x+j, y+i, *sprite++)){
        printf("Error drawing pixel (%d, %d)", x+i, j+i);
        return 1;
      }
    }
  }
  return 0;
}

int (draw_xpm_loaded)(uint16_t x, uint16_t y, xpm_image_t img, uint8_t *sprite){
  if(sprite == NULL){
    printf("Error loading sprite\n");
    return 1;
  }

  for(unsigned i=0; i<img.height; i++){
    for(unsigned j=0; j<img.width; j++){
      if(vg_draw_pixel(x+j, y+i, *sprite++)){
        printf("Error drawing pixel (%d, %d)", x+i, j+i);
        return 1;
      }
    }
  }
  return 0;
}

int (erase_screen)(uint16_t x, uint16_t y, xpm_image_t img){
  if(vg_draw_rectangle(x, y, img.width, img.height, 0)) return 1;
  return 0;
}

bool pos_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed){
  if(verticalMovement){
    if(positiveMovement){*y = (*y+speed>yf) ? yf : *y+speed;}
    else{*y = (*y-speed<yf) ? yf : *y-speed;}
  }
  else{
    if(positiveMovement){*x = (*x+speed>xf) ? xf : *x+speed;}
    else{*x = (*x-speed<xf) ? xf : *x-speed;}
  }

  return true;
}

bool neg_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int* frameCounter){
  *frameCounter = *frameCounter + 1;
  if(*frameCounter % abs(speed)==0){
    if(verticalMovement){
      if(positiveMovement){*y = (*y+1>yf) ? yf : *y+1;}
      else{*y = (*y-1<yf) ? yf : *y-1;}
    }
    else{
      if(positiveMovement){*x = (*x+1>xf) ? xf : *x+1;}
      else{*x = (*x-1<xf) ? xf : *x-1;}
    }
    return true;
  }
  return false;
}
