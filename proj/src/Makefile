PROG=proj

.PATH: ${.CURDIR}/project
.PATH: ${.CURDIR}/lib/timer
.PATH: ${.CURDIR}/lib/utils
.PATH: ${.CURDIR}/lib/kbc
.PATH: ${.CURDIR}/lib/graphics
.PATH: ${.CURDIR}/lib/rtc

SRCS= timer.c utils.c main.c kbc.c keyboard.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
