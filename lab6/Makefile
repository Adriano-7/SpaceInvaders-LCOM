# name of the program (Minix service)
PROG=lab5

# source code files to be compiled
SRCS = lab5.c video.c timer.c utils.c keyboard.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
