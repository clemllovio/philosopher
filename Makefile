# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME		=	philo

# ---- Files ---- #

HEAD		=	headers/philo.h\
				ft_dprintf/ft_dprintf.h

SRC			=	sources/fork.c\
				sources/init_philo.c\
				sources/launch_philo.c\
				sources/main.c\
				sources/parsing.c\
				sources/print_messages.c\
				sources/routine.c\
				sources/utils.c

# ---- Directories ---- #
DIR_HEAD 	= 	headers/

DIR_OBJS	=	.objs

DIR_LIB		=	ft_dprintf/

# ---- Paths ---- #

LIBRARY		=	ft_dprintf/libftprintf.a

OBJS 		=	${addprefix ${DIR_OBJS}/, ${SRC:.c=.o}}

# ---- Commands ---- #

RMF				=	rm -rf

# ====================== FLAGS AND COMPILATION ====================== #

# ---- Compilation flags ---- #

CC 				= cc

CFLAGS 			= -Wall  -Wextra -Werror -pthread -fsanitize=thread -g3 -I ${DIR_HEAD} -I ${DIR_LIB}

# ====================== RULES ====================== #

# ---- Compilation rules ---- #

all :
	${MAKE} lib
	${MAKE} ${NAME}

${NAME}: ${OBJS} ${LIBRARY}
	${CC} ${CFLAGS} $^ ${LIBRARY} -o $@

${DIR_OBJS}/%.o: %.c ${HEAD}
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

# ---- Library ---- #

lib :
	${MAKE} -C ./ft_dprintf

# ---- Clean rules --- #

clean :
	$(MAKE) -C ft_dprintf clean
	${RMF} ${DIR_OBJS}

fclean : clean 
	$(MAKE) -C ft_dprintf fclean
	${RMF}  ${NAME}

re : fclean
	${MAKE} all

.PHONY: all lib clean fclean re