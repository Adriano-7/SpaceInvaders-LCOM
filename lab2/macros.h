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

#define TIMER_STATUS_ACCESS (BIT(4) | BIT(5))
#define TIMER_STATUS_OP_MODE (BIT(3) | BIT(2) | BIT(1))
