/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:39:55 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/26 20:34:54 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/ioctl.h>
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
	char 			*str;
	struct s_list	*next;
	struct s_list	*prev;
	struct s_msc	*msc;
}			t_list;

typedef struct s_msc
{
	t_list	*lex;
	bool	loop;
	char	*input;
	char	*env_user;
	char	*env_path;
	char	*env_cwd;
	char	*env_home_dir;
	char	*env_tilde_cwd;
	char	*prompt;
	char	**env_cpy;
}				t_msc;

//global variable
extern int	g_sig_status;

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

//prompt.c
void	set_prompt_and_cwd(t_msc *msc);

//signals.c
void	handle_sigint(int sig);

//list_utils1.c
t_list	*ft_lstnew(t_msc *ms);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
t_list  *init_lst(t_msc *msc, char **input);

//lex_funcs.c
void    del_tmp(char **tmp);
void	input_lexer(t_msc *msc);
void    ft_printlist(t_list *lst);

//lex_utils.c
int quote_checker(const char *s);
void	skip_quotes(const char *s, int *i, int *wc);
char    *get_qt(char *s, char q);


//lex_split.c
int	isws(const char c);
void	*del_split(char **words, int i);
int	get_wc(const char *s);
char	*get_wd(char *s);
char	**lex_split(const char *s);

#endif
