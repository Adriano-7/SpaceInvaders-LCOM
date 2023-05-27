#include <lcom/lcf.h>
#include "game.h"
#include "devices/video.h"

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/g5/trace.txt");
  
  lcf_log_output("/home/lcom/labs/g5/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  return lcf_cleanup();
}

int proj_main_loop(int argc, char *argv[]) {
  
  if(map_phys_mem(0x105)){
    printf("Error mapping phys memmory\n");
    return 1;
  }
  
  if(video_set_mode(0x105)){
    printf("Error setting graphics mode\n");
    return 1;
  }

  if (game_loop()) {
    printf("Error entering game loop\n");
    return 1;
  }

  return 0;
}
