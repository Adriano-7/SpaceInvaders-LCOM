#include "graphics.h"

struct minix_mem_range mem_range;
vbe_mode_info_t mode_info;
uint8_t* video_mem;

int (set_graphics_mode)(uint16_t submode) {
  reg86_t reg;
  memset(&reg, 0, sizeof(reg));

  reg.ah = GR_AH;
  reg.al = GR_AL;
  reg.bx = GR_BX(submode);
  reg.intno = GR_INTNO;
  
  if(sys_int86(&reg) != OK){
    printf("Error setting up graphics mode\n");
    return 1;
  }
  return 0;
}

int map_phys_mem(uint16_t mode){
  memset(&mode_info, 0, sizeof(mode_info));
  if(vbe_get_mode_info(mode, &mode_info)){
    printf("Error obtaining mode_info\n");
    return 1;
  }

  int BytesPerPixel = (mode_info.BitsPerPixel+7)/8;
  int vram_base = mode_info.PhysBasePtr;
  int vram_size = (mode_info.XResolution*mode_info.YResolution)*BytesPerPixel;

  mem_range.mr_base = vram_base;
  mem_range.mr_limit = mode_info.PhysBasePtr + vram_size;

  if(OK != sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem_range)){
      printf("Error mapping physical to virtual memory\n");
      return 1;
  }

  video_mem = vm_map_phys(SELF, (void *)mem_range.mr_base, vram_size);
  if(video_mem == MAP_FAILED){
    printf("Couldn't map video memory\n");
    return 1;
  }
  return 0;
}

int (pixel_index)(uint16_t x, uint16_t y, uint16_t BytesPerPixel){
  if(x>mode_info.XResolution){
    printf("The x position is greater than the resolution allowed\n");
    return -1;
  }

  if(y>mode_info.YResolution){
    printf("The y position is greater than the resolution allowed\n");
    return -1;
  }

  return (y*mode_info.XResolution+x)*BytesPerPixel;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
  uint16_t BytesPerPixel = (mode_info.BitsPerPixel+7)/8;

  int index = pixel_index(x, y, BytesPerPixel);
  if(index==-1){printf("Coordinate not allowed\n");}

  if(memcpy(&video_mem[index], &color, BytesPerPixel)==NULL){
    printf("Error drawing pixel\n");
    return 1;
  }

  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(unsigned i=0; i<len; i++){
    if(vg_draw_pixel(x+i, y, color)){
      printf("Error pixel with coordinates (%d, %d)\n", x+i, y);
      return 1;
    }
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(unsigned i=0; i<height; i++){
    if(vg_draw_hline(x, y+i, width, color)){
      printf("Error drawing line  %d\n", i);
      return 1;
    }
  }
  return 0;
}

uint32_t (color_indexed)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles){
  return (first + (row*no_rectangles+col)*step) % (1 << mode_info.BitsPerPixel);
}

uint32_t (color_direct)(uint32_t r, uint32_t g, uint32_t b){
  return (r<<mode_info.RedFieldPosition) | (g << mode_info.GreenFieldPosition) | (b << mode_info.BlueFieldPosition);
}

uint32_t (First_R)(uint32_t first){
  return (first >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize) - 1);
}

uint32_t (First_G)(uint32_t first){
  return (first >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize) - 1);
}

uint32_t (First_B)(uint32_t first){
  return (first >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize) - 1);
}

uint32_t (R)(unsigned row, unsigned col, uint8_t step, uint32_t first){
  return (First_R(first) + col*step) % (1 << mode_info.RedMaskSize);
}

uint32_t (G)(unsigned row, unsigned col, uint8_t step, uint32_t first){
  return (First_G(first) + row*step) % (1 << mode_info.GreenMaskSize);
}

uint32_t (B)(unsigned row, unsigned col, uint8_t step, uint32_t first){
  return (First_B(first) + (row+col)*step) % (1 << mode_info.BlueMaskSize);
}

uint32_t (get_color)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles){
  if(mode_info.MemoryModel == DIRECT_COLOR_MODE){
    return color_direct(R(row, col, step, first), G(row, col, step, first), B(row, col, step, first));
  }
  else{
    return color_indexed(row, col, step, first, no_rectangles);
  }
}

int (draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y){
  xpm_image_t xpm_sprite;
  uint8_t* sprite = xpm_load(xpm, XPM_INDEXED, &xpm_sprite);
  if(sprite == NULL){
    printf("Error loading sprite\n");
    return 1;
  }

  for(unsigned i=0; i<xpm_sprite.height; i++){
    for(unsigned j=0; j<xpm_sprite.width; j++){
      if(vg_draw_pixel(x+j, y+i, *sprite++)){
        printf("Error drawing pixel\n");
        return 1;
      }
    }
  }
  return 0;
}
