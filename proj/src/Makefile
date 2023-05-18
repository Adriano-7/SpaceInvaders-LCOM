PROG=proj

.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/controllers
.PATH: ${.CURDIR}/controllers/game
.PATH: ${.CURDIR}/controllers/menu
.PATH: ${.CURDIR}/model
.PATH: ${.CURDIR}/model/menu
.PATH: ${.CURDIR}/model/game





SRCS= timer.c utils.c main.c kbc.c keyboard.c graphics.c game.c handleInterrupt.c player.c menu.c gameObject.c keys.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
