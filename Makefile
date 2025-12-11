CFLAGS= cc -Wall -Wextra -Werror
OBJ= ft_printf.o ft_printf_cases.o ft_printf_hex.o
NAME= libftprintf.a

all : $(NAME)

%.o : %.c ft_printf.h
	$(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ) 

clean :
	$(RM) $(OBJ)

fclean :
	$(RM) $(NAME) $(OBJ)

re : fclean all

.PHONY : all clean fclean re
