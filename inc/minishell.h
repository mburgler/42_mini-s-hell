/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:39:55 by mburgler          #+#    #+#             */
/*   Updated: 2023/08/08 16:05:55 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../MY_LIB/ft_printf/ft_printf.h"
# include "../MY_LIB/ft_printf2/ft_printf2.h"
# include "../MY_LIB/get_next_line/get_next_line_bonus.h"

// typedef struct s_env
// {
// 	char	*name;
// 	char	*value;
// }				t_env;

// typedef struct s_cmd
// {
// 	char	**args;
// 	char	*path;
// }				t_cmd;

typedef struct s_list
{
	char *str;
	struct s_list	*next;
}			t_list;

typedef struct msc
{
	t_list	*list;
}				t_msc;

//parsing.c
int	parsing(int i_args, char **strs, t_msc *msc);
int	ft_isvalidstr(char *str);
int	ft_isvalidchar(char c);
int		ft_isseparator(char c);
int		ft_isquote(char c);
int		ft_iswhitespace(char c);

int	ft_isvalidlist(t_list *list);
int	ft_isvalidcmd(t_list *list);
int	ft_isvalidpipe(t_list *list);
int	ft_isvalidredir(t_list *list);

//free_stuff.c
void	free_null(void **ptr);
void	free_all(t_msc *msc);

//list_utils.c
void ft_lstadd_back(t_list **alst, t_list *new);
t_list *ft_lstnew(void *content);
t_list *ft_lstlast(t_list *lst);

//debug.c
void	debug_print_list(t_list *list);
#endif
