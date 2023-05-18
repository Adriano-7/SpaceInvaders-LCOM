#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define IRQ_KEYBOARD    1

#define BREAK_ESC       0x81
#define BREAK_CODE       BIT(7)
#define TWO_BYTES       0xE0
#define ENABLE_INT      BIT(0)

#define TIMEOUT_ERROR   BIT(6)
#define PARITY_ERROR    BIT(7)
#define FULL_OUT_BUFFER BIT(0)
#define FULL_IN_BUFFER  BIT(1)
#define AUX             BIT(5)

#define KBC_OUT_BUF     0x60
#define KBC_STATUS_REG  0x64
#define KBC_IN_CMD      0x64
#define KBC_OUT_CMD     0x60
#define KBC_READ_CMD    0x20
#define KBC_WRITE_CMD   0x60

#define WAIT_KBC        20000
#define MAX_ATTEMPS     10

#define A_KEY           0x1E
#define B_KEY           0x30
#define C_KEY           0x2E
#define D_KEY           0x20
#define E_KEY           0x12
#define F_KEY           0x21
#define G_KEY           0x22
#define H_KEY           0x23
#define I_KEY           0x17
#define J_KEY           0x24
#define K_KEY           0x25
#define L_KEY           0x26
#define M_KEY           0x32
#define N_KEY           0x31
#define O_KEY           0x18
#define P_KEY           0x19
#define Q_KEY           0x10
#define R_KEY           0x13
#define S_KEY           0x1F
#define T_KEY           0x14
#define U_KEY           0x16
#define V_KEY           0x2F
#define W_KEY           0x11
#define X_KEY           0x2D
#define Y_KEY           0x15
#define Z_KEY           0x2C

#define ZERO_KEY        0x0B
#define ONE_KEY         0x02
#define TWO_KEY         0x03
#define THREE_KEY       0x04
#define FOUR_KEY        0x05
#define FIVE_KEY        0x06
#define SIX_KEY         0x07
#define SEVEN_KEY       0x08
#define EIGHT_KEY       0x09
#define NINE_KEY        0x0A

#endif /* _LCOM_I8042_H_ */
