PROG=proj

.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/controllers
.PATH: ${.CURDIR}/controllers/game
.PATH: ${.CURDIR}/controllers/game/entities
.PATH: ${.CURDIR}/controllers/menu
.PATH: ${.CURDIR}/model
.PATH: ${.CURDIR}/model/menu
.PATH: ${.CURDIR}/model/game
.PATH: ${.CURDIR}/xpm

SRCS= video.c keyboard.c timer.c rtc.c utils.c mouse.c gameController.c monsterController.c playerController.c bulletController.c handleInterrupt.c keys.c monster.c player.c bullet.c menu.c cursor.c option.c drawableObject.c loadXpm.c game.c main.c map.c menuController.c state.c leaderboardController.c leaderboard.c gameOver.c gameOverController.c

CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
