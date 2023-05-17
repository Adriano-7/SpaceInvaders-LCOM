#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define IRQ_KEYBOARD     1
#define IRQ_MOUSE        12
 
#define BREAK_ESC        0x81
#define MAKE_CODE        BIT(7)
#define TWO_BYTES        0xE0
#define ENABLE_INT       BIT(0)
 
#define TIMEOUT_ERROR    BIT(6)
#define PARITY_ERROR     BIT(7)
#define FULL_OUT_BUFFER  BIT(0)
#define FULL_IN_BUFFER   BIT(1)
#define AUX              BIT(5)

#define MOUSE_ENABLE_DATA_REPORTING  0xF4
 
#define KBC_STATUS_REG   0x64
#define KBC_IN_CMD       0x64
#define KBC_OUT_CMD      0x60
#define KBC_READ_CMD     0x20
#define KBC_WRITE_CMD    0x60

#define MAX_TRIES        100 
#define KBC_DELAY        20000

#define MOUSE_LB         BIT(0)
#define MOUSE_RB         BIT(1)
#define MOUSE_MB         BIT(2)
#define MOUSE_FIRST_BYTE BIT(3) 
#define MOUSE_X_MSB      BIT(4)
#define MOUSE_Y_MSB      BIT(5)
#define MOUSE_X_OVF      BIT(6)
#define MOUSE_Y_OVF      BIT(7) 
#define MOUSE_ACK        0xFA
#define MOUSE_NACK       0xFE

#define MOUSE_WRITE_BYTE 0xD4
#define MOUSE_DISABLE_DATA_REPORTING 0xF5
#define MOUSE_ENABLE_DATA_REPORTING 0xF4

#endif
