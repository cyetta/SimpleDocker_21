NAME	=	fcgi_hello

SRCS	=	fcgi_hello_spawn.c

OBJS	=	${SRCS:%.c=%.o}

CC		=	gcc

RM		=	rm -f

DIR_RDLINE = ${HOME}/.brew/opt/readline

CCFLAGS	=	-Wall -Wextra -Werror

# on mac used fcgi installed in brew
# brew install fcgi
# To install Homebrew on Mac - https://github.com/kube/42homebrew
# Linux:
# sudo apt update 
# sudo apt install libfcgi-dev
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	DIR_FCGI = 
	FCGI_LIB = -lfcgi
# Define macro LINUX
	CCFLAGS += -D LINUX
endif
ifeq ($(UNAME_S),Darwin)
	DIR_FCGI = $(shell brew --prefix fcgi)
	FCGI_INC = -I$(DIR_FCGI)/include
	FCGI_LIB = -L $(DIR_FCGI)/lib -lfcgi
# Define macro OSX
	CCFLAGS += -D OSX
endif

.PHONY:		all clean fclean re debug

DPDS	= ${SRCS:.c=.d}

all:		${NAME}

%.o: %.c
	${CC} ${CCFLAGS} ${DFLAG} -MMD -c $< -o $@ $(FCGI_INC)

include ${wildcard ${DPDS}}

${NAME}:	${OBJS}
			${CC} ${CCFLAGS} ${DFLAG} -o ${NAME} ${OBJS} $(FCGI_LIB)
			${RM} ${DPDS}

debug:
			${MAKE} DFLAG="-g3" ${NAME}
clean:
			${RM} ${OBJS} ${DPDS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

test:
			./${NAME}