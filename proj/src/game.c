#include <lcom/lcf.h>
#include "controllers/handleInterrupt.h"
#include "game.h"
#include "devices/keyboard.h"
#include "devices/timer.h"
#include "devices/vbe.h"
#include "devices/graphics.h"
#include "model/game/player.h"
#include "model/gameObject.h"

#include "xpm/loadXpm.h"

#include "state.h"

extern uint8_t output;
extern vbe_mode_info_t mode_info;

extern xpm_image_t game_xpm[4];
extern uint8_t* game_xpm_map[4];

Player* player;

int game_loop(){
	//bool running = true;
	enum State state = GAME;

	int ipc_status, r;
	message msg;

	//Keyboard
	bool secondByte = false;
	uint8_t bytes[2];
	uint8_t keyboard_bit_no;

	//Timer
	uint8_t timer_bit_no;

	loadXpms();
	GameObject* gameObject = createGameObject((mode_info.XResolution/2)-(game_xpm[0].width/2), mode_info.YResolution-game_xpm[0].height, 30, game_xpm[0] ,game_xpm_map[0],true);
	player = createPlayer(gameObject);

	if(timer_subscribe_int(&timer_bit_no)){
	printf("Error while subscribing timer interrupt\n");
	return 1;
	}

	if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
	printf("Error subscribing keyboard interrupts\n");
	return 1;
	}

	//2nd Initialize game
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
				handle_keyboard(state,bytes,player);
			}
			else{
				bytes[0] = output;
				if(output==0xE0){
				secondByte = true;
				}
				else{
				handle_keyboard(state,bytes,player);
				}
			}
			}
			if (msg.m_notify.interrupts & BIT(timer_bit_no)){
				timer_int_handler();
				drawGameObject(gameObject);
			}
			break;
			}
		}
	} 


	//3rd Loop/Receive interrupts

	cleanXpms();

	//4th Unsubscribe interrupts
	if(timer_unsubscribe_int()){
	printf("Error while unsubscribing timer interrupt\n");
	return 1;
	}

	if(keyboard_unsubscribe_interrupts()){
	printf("Error unsubscribing keyboard interrupts\n");
	return 1;
	}

	if(vg_exit()){
	printf("Error exiting graphics mode\n");
	return 1;
	}

	return 0;
}
