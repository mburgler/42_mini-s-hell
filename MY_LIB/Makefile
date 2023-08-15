NAME = libftprintf.a

DIR_LIB = libft

SRC := ft_printf/ft_printf_helper.c ft_printf/ft_printf.c \
			ft_printf2/ft_printf2_helper.c ft_printf2/ft_printf2.c \
			get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c \

SRC_LIB = $(DIR_LIB)/*.c

OBJS = *.o

OBJS_LIB = $(DIR_LIB)/*.o

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_LIB)
	@ar rcs $@ $^

$(OBJS): $(SRC)
	@gcc -Wall -Werror -Wextra -c $^

$(OBJS_LIB): $(SRC_LIB)
	@$(MAKE) -s -C $(DIR_LIB)

clean:
	@$(RM) $(OBJS) $(OBJS_LIB)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
