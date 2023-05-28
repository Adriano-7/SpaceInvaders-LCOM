/*Timer*/
#define TIMER_0_IRQ 0
#define TIMER_CLOCK_FREQ 1193182

#define TIMER_REG(timer) 0x40+timer
#define TIMER_CNTRL_REG 0x43

#define TIMER_RBK (BIT(7) | BIT(6))
#define TIMER_RBK_NOT_COUNT BIT(5)
#define TIMER_RBK_NOT_STATUS BIT(4)
#define TIMER_RBK_SEL(timer) BIT((timer) + 1)

#define TIMER_CNTRL_WORD_SEL(timer) (timer << 6)
#define TIMER_CNTRL_INIT_LSB_MSB (BIT(4) | BIT(5))

#define TIMER_ST_ACCESS (BIT(4) | BIT(5))
#define TIMER_ST_OP_MODE (BIT(3) | BIT(2) | BIT(1))

/*Keyboard*/
#define KEYBOARD_IRQ 1

#define KEYBOARD_ST_REG 0x64
#define KEYBOARD_CMD_REG 0x64
#define KEYBOARD_OUT_BUF 0x60

#define KEYBOARD_ST_PARITY BIT(7)
#define KEYBOARD_ST_TIMEOUT BIT(6)
#define KEYBOARD_ST_IBF BIT(1)
#define KEYBOARD_ST_OBF BIT(0)
#define KEYBOARD_ST_AUX BIT(5)

#define KEYBOARD_TWO_BYTE 0xE0

#define KEYBOARD_SCANCODE_BREAK BIT(7)

/*Keys*/
#define KEY_ESC_BREAK 0x81
