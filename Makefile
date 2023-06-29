# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME		=	minishell

# ---- Files ---- #

HEAD		=	header/philo.h

SRC			=	sources/main.c

# ---- Directories ---- #
DIR_HEAD 	= 	headers/

DIR_OBJS	=	.objs

# ---- Paths ---- #

LIBRARY		=	${DIR_LIB}/libft.a 

OBJS 		=	${addprefix ${DIR_OBJS}/, ${SRC:.c=.o}}

# ---- Commands ---- #

RMF				=	rm -rf

# ====================== FLAGS AND COMPILATION ====================== #

# ---- Compilation flags ---- #

CC 				= cc

CFLAGS 			= -Wall  -Wextra -Werror -I ${DIR_HEAD}

# ====================== RULES ====================== #

# ---- Compilation rules ---- #

all :
	${MAKE} ${NAME}

${NAME}: ${OBJS} ${LIBRARY}
	${CC} ${CFLAGS} $^ ${LIBRARY} -o $@ -lreadline

${DIR_OBJS}/%.o: %.c ${HEAD}
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

# ---- Clean rules --- #

clean :
	${RMF} ${DIR_OBJS}

fclean : clean 
	${RMF}  ${NAME}

re : fclean
	${MAKE} all

.PHONY: all lib clean fclean re