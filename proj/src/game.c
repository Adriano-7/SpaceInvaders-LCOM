#include "game.h"

enum State* state = &(enum State){MENU};

Leaderboard_t* leaderboard;

int game_loop(){
	int ipc_status, r;
	message msg;

	uint8_t keyboard_bit_no, timer_bit_no, mouse_bit_no, rtc_bit_no;


	loadXpms();
	Map_t* map =  loadGame();
	Menu_t* menu = loadMenu();
	leaderboard = createLeaderboard();

	if(timer_subscribe_int(&timer_bit_no)){
		printf("Error while subscribing timer interrupt\n");
		return 1;
	}

	if(keyboard_subscribe_int(&keyboard_bit_no)){
		printf("Error subscribing keyboard interrupts\n");
		return 1;
	}

	if (enable_data_report()){
    	printf("Error while enabling the mouse data report\n");
    	return 1;
  	}

  	if (mouse_subscribe_int(&mouse_bit_no)){
    	printf("Error while subscribing the mouse interrupts\n");
    	return 1;
  	}

	if(rtc_subscribe_int(&rtc_bit_no)){
  		printf("Error while subscribing the rtc interrupts\n");
  		return 1;
  	}

	while(*state != EXIT){
	if((r = driver_receive(ANY, &msg, &ipc_status))) {
		printf("driver_receive failed with: %d", r);
		continue;
	}

	if (is_ipc_notify(ipc_status)) {
		switch (_ENDPOINT_P(msg.m_source)) {
		case HARDWARE:
			if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
				keyboard_int_handler();
				if(keyboard_parse_output()){
					handle_keyboard(state, map, menu);
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
			if (msg.m_notify.interrupts & BIT(rtc_bit_no)){
				rtc_int_handler();
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

	if(keyboard_unsubscribe_int()){
		printf("Error unsubscribing keyboard interrupts\n");
		return 1;
	}

	if (disable_data_report()){
    	printf("Error while disabling the mouse data report\n");
    	return 1;
  	}

  	if (mouse_unsubscribe_int()){
    	printf("Error while unsubscribing the mouse interrupts\n");
    	return 1;
  	}

	if(rtc_unsubscribe_int()){
  		printf("Error while unsubscribing the rtc interrupts\n");
  		return 1;
  	}

	if(vg_exit()){
		printf("Error exiting graphics mode\n");
		return 1;
	}

	return 0;
}
