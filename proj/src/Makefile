PROG=proj

.PATH: ${.CURDIR}/Devices
.PATH: ${.CURDIR}/controllers

SRCS= timer.c utils.c main.c kbc.c keyboard.c graphics.c game.c keyboard_controller.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
