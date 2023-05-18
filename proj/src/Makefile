PROG=proj

.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/interrupts
.PATH: ${.CURDIR}/interrupts/game
.PATH: ${.CURDIR}/interrupts/menu
.PATH: ${.CURDIR}/model
.PATH: ${.CURDIR}/model/menu
.PATH: ${.CURDIR}/model/game
.PATH: ${.CURDIR}/xpm





SRCS= timer.c utils.c main.c kbc.c keyboard.c graphics.c game.c handleInterrupt.c player.c menu.c gameObject.c keys.c loadXpm.c monster.c gameController.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
