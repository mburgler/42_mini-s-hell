/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:39:55 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/20 19:31:57 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
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
	bool	loop;
	char	*input;
	char	*env_user;
	char	*env_path;
	char	*prompt;
	char	**env_cpy;
}				t_msc;

//free_stuff.c
void	free_null(void **ptr);
void	ft_free_arr(char **strs);
void	free_all(t_msc *msc);

//main.c
void	set_prompt(t_msc *msc);
void	init_msc(t_msc *msc, char **env);

//dup_utils.c
int	ft_arrlen(char **str);
char	**ft_dup_arr(char **strs);
#endif