NAME = libftprintf.a

CFLAGS = -Wall -Werror -Wextra

SRCS =	ft_dprintf.c\
		ft_dprint_char.c\
		ft_dprint_nbr.c\
		ft_check_args.c\

OBJS = $(SRCS:.c=.o)

RM = rm -f

HEADERS = ft_printf.h

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I .

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY = all clean fclean re bonus
