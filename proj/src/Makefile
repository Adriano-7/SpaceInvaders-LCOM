PROG=proj

.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/interrupts
.PATH: ${.CURDIR}/interrupts/game
.PATH: ${.CURDIR}/interrupts/menu
.PATH: ${.CURDIR}/model
.PATH: ${.CURDIR}/model/menu
.PATH: ${.CURDIR}/model/game
.PATH: ${.CURDIR}/xpm

SRCS= graphics.c kbc.c keyboard.c timer.c utils.c gameController.c entitiesController.c handleInterrupt.c keys.c monster.c player.c bullet.c menu.c drawableObject.c loadXpm.c game.c main.c map.c menuController.c state.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
