# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 10:55:14 by mburgler          #+#    #+#              #
#    Updated: 2023/11/13 17:05:57 by abektimi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC          := cc
FLAGS       := -Wall -Wextra -Werror -g

ifeq ($(shell uname -s), Darwin)
    $(info "Using macOS settings")
    SUPP_FLAGS := -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline
else
    $(info "Using Linux settings")
    SUPP_FLAGS := -lreadline -lncurses
endif


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
                    src/free_stuff.c \
					src/error_handling.c \
                    src/env_dup.c \
					src/env_utils.c \
                    src/signal.c \
                    src/main.c \
                    src/list_utils1.c \
					src/exp_func.c \
					src/exp_utils1.c \
					src/exp_utils2.c \
					src/op_func.c \
                    src/lex_funcs.c \
                    src/lex_split.c \
                    src/lex_utils1.c \
                    src/lex_utils2.c \
					src/lex_utils3.c \
					src/kill_quotes.c \
                    src/cmd_utils1.c \
                    src/cmd_utils2.c \
                    src/in_out_files.c \
                    src/exec_funcs.c \
                    src/exec_prep.c \
                    src/exec_utils1.c \
                    src/exec_utils2.c \
                    src/exec_utils3.c \
                    src/builtin_env.c \
					src/builtin_export1.c \
					src/builtin_export2.c \
					src/builtin_echo.c \
					src/builtin_pwd.c \
					src/builtin_cd.c \
					src/builtin_unset.c \
                    src/set_fds.c

OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
BLUE        := \033[1;34m
CYAN        := \033[1;36m
RM          := rm -f

${NAME}:    ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${SUPP_FLAGS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:        ${NAME}

bonus:      all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:     clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:         fclean all

leak:	   all
	if [ ! -e leaks.supp ]; then \
		printf "{" > leaks.supp; \
		printf "\n\tignore_libreadline_errors" >> leaks.supp; \
		printf "\n\tMemcheck:Leak" >> leaks.supp; \
		printf "\n\t..." >> leaks.supp; \
		printf "\n\tobj:*/libreadline.so.*" >> leaks.supp; \
		printf "\n}" >> leaks.supp; \
		printf "FILE FOR LEAK SURPESSION CREATED\n"; \
	fi
	valgrind --leak-check=full --tool=memcheck \
		--track-origins=yes --show-leak-kinds=all \
		--suppressions=leaks.supp --track-fds=yes ./minishell
				
				
				
.PHONY:     all clean fclean re
