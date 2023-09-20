#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC        := cc
FLAGS    := -Wall -Wextra -Werror -g
SUPP_FlAGS := -lreadline -lncurses
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      MY_LIB/ft_printf2/ft_printf2_helper.c \
                          MY_LIB/ft_printf2/ft_printf2.c \
                          MY_LIB/libft/ft_strnstr.c \
                          MY_LIB/libft/ft_isdigit.c \
                          MY_LIB/libft/ft_putstr_fd.c \
                          MY_LIB/libft/ft_strlcpy.c \
                          MY_LIB/libft/ft_strlen.c \
                          MY_LIB/libft/ft_memcmp.c \
                          MY_LIB/libft/ft_putnbr_fd.c \
                          MY_LIB/libft/ft_strchr.c \
                          MY_LIB/libft/ft_striteri.c \
                          MY_LIB/libft/ft_bzero.c \
                          MY_LIB/libft/ft_strjoin.c \
                          MY_LIB/libft/ft_isascii.c \
                          MY_LIB/libft/ft_memcpy.c \
                          MY_LIB/libft/ft_isprint.c \
                          MY_LIB/libft/ft_putendl_fd.c \
                          MY_LIB/libft/ft_toupper.c \
                          MY_LIB/libft/ft_split.c \
                          MY_LIB/libft/ft_strrchr.c \
                          MY_LIB/libft/ft_isalpha.c \
                          MY_LIB/libft/ft_memchr.c \
                          MY_LIB/libft/ft_putchar_fd.c \
                          MY_LIB/libft/ft_memset.c \
                          MY_LIB/libft/ft_substr.c \
                          MY_LIB/libft/ft_strncmp.c \
                          MY_LIB/libft/ft_strmapi.c \
                          MY_LIB/libft/ft_strtrim.c \
                          MY_LIB/libft/ft_memmove.c \
                          MY_LIB/libft/ft_strlcat.c \
                          MY_LIB/libft/ft_calloc.c \
                          MY_LIB/libft/ft_strdup.c \
                          MY_LIB/libft/ft_atoi.c \
                          MY_LIB/libft/ft_isalnum.c \
                          MY_LIB/libft/ft_itoa.c \
                          MY_LIB/libft/ft_tolower.c \
                          MY_LIB/ft_printf/ft_printf_helper.c \
                          MY_LIB/ft_printf/ft_printf.c \
                          MY_LIB/get_next_line/get_next_line_bonus.c \
                          MY_LIB/get_next_line/get_next_line_utils_bonus.c \
                          src/parsing.c \
                          src/free_stuff.c \
                          src/list_utils.c \
						  src/debug.c \
                          src/main.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${SUPP_FLAGS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


