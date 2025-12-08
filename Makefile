CFLAGS= cc -Wall -Wextra -Werror
OBJ=ft_printf.o
NAME= libftprintf.a

all : $(NAME)

%.o : %.c ft_printf.h
	$(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ) 

clean :
	rm -f $(NAME)

fclean :
	rm -f $(NAME) $(OBJ)

.PHONY : all clean fclean re
