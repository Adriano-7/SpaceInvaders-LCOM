# name of the program (Minix service)
PROG=lab4

# source code files to be compiled
SRCS = lab4.c utils.c mouse.c timer.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
