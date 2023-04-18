#include "graphics.h"

static void *video_mem;
vbe_mode_info_t info_mode;
struct minix_mem_range memory_range;

unsigned int vram_base;
unsigned int vram_size;
int r;

int set_video_mem(uint16_t mode){
  memset(&info_mode, 0, sizeof(info_mode));

  if(vbe_get_mode_info(mode, &info_mode) != 0){
    printf("vbe_get_mode_info() -> error getting video mode\n");
    return 1;
  }

  int hres = info_mode.XResolution;
  int vres = info_mode.YResolution;
  int bits_per_pixel = info_mode.BitsPerPixel;

  vram_base = info_mode.PhysBasePtr;
  vram_size = hres*vres*(bits_per_pixel+7)/8;

  memory_range.mr_base = info_mode.PhysBasePtr;
  memory_range.mr_limit = memory_range.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &memory_range)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  video_mem = vm_map_phys(SELF, (void *)memory_range.mr_base, vram_size);

  if(video_mem == MAP_FAILED){
    panic("couldn't map video memory");
  }

  return 0;
}

int set_graphics_mode(uint16_t submode){
  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.intno = 0x10;
  r86.ah = 0x4F;
  r86.al = 0x02; 

  r86.ax = 0x4F02;
  r86.bx = submode | BIT(14);

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }
  return 0;
}

