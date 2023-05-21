PROG=proj

.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/interrupts
.PATH: ${.CURDIR}/interrupts/game
.PATH: ${.CURDIR}/interrupts/menu
.PATH: ${.CURDIR}/model
.PATH: ${.CURDIR}/model/menu
.PATH: ${.CURDIR}/model/game
.PATH: ${.CURDIR}/xpm





SRCS= graphics.c kbc.c keyboard.c timer.c utils.c gameController.c handleInterrupt.c keys.c mapLoader.c monster.c player.c menu.c gameObject.c loadXpm.c game.c main.c map.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
