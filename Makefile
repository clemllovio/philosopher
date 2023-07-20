# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME		=	philo

# ---- Files ---- #

HEAD		=	headers/philo.h

SRC			=	sources/main.c\
				sources/parsing.c\
				sources/print_error.c

# ---- Directories ---- #
DIR_HEAD 	= 	headers/

DIR_OBJS	=	.objs

# ---- Paths ---- #

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

${NAME}: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

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

.PHONY: all clean fclean re