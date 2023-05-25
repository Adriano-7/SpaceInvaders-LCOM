#include "game.h"

extern uint8_t output;
extern struct packet pp;

enum State* state = &(enum State){MENU};

int game_loop(){
	int ipc_status, r;
	message msg;

	bool secondByte = false;
	uint8_t bytes[2];
	uint8_t keyboard_bit_no, timer_bit_no, mouse_bit_no;

	loadXpms();
	Map_t* map =  loadGame();
	Menu_t* menu = loadMenu();

	if(timer_subscribe_int(&timer_bit_no)){
		printf("Error while subscribing timer interrupt\n");
		return 1;
	}

	if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
		printf("Error subscribing keyboard interrupts\n");
		return 1;
	}

	if (enable_data_report()){
    	printf("Error while enabling the mouse data report\n");
    	return 1;
  	}

  	if (mouse_subscribe_interrupts(&mouse_bit_no)){
    	printf("Error while subscribing the mouse interrupts\n");
    	return 1;
  	}

	while(output != BREAK_ESC){
	if((r = driver_receive(ANY, &msg, &ipc_status))) {
		printf("driver_receive failed with: %d", r);
		continue;
	}

	if (is_ipc_notify(ipc_status)) {
		switch (_ENDPOINT_P(msg.m_source)) {
		case HARDWARE:
			if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
				kbc_ih();
				if(secondByte){
					secondByte=false;
					bytes[1]=output;
					handle_keyboard(state, bytes, map, menu);
				}
				else{
					bytes[0] = output;
					if(output==0xE0){
						secondByte = true;
					}
					else{
						handle_keyboard(state, bytes,map, menu);
					}
				}
			}

			if (msg.m_notify.interrupts & BIT(timer_bit_no)){
				timer_int_handler();
				handle_timer(state, map, menu);
			}

			if (msg.m_notify.interrupts & BIT(mouse_bit_no)){
          		mouse_ih();

          		if(mouse_parse_output()){            
            		mouse_build_packet();
					handle_mouse(state, map, menu);
          		}
        	}
			break;
			}
		}
	} 

	destroyMap(map);

	if(timer_unsubscribe_int()){
		printf("Error while unsubscribing timer interrupt\n");
		return 1;
	}

	if(keyboard_unsubscribe_interrupts()){
		printf("Error unsubscribing keyboard interrupts\n");
		return 1;
	}

	if (disable_data_report()){
    	printf("Error while disabling the mouse data report\n");
    	return 1;
  	}

  	if (mouse_unsubscribe_interrupts()){
    	printf("Error while unsubscribing the mouse interrupts\n");
    	return 1;
  	}

	if(vg_exit()){
		printf("Error exiting graphics mode\n");
		return 1;
	}

	return 0;
}
