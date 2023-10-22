/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:39:55 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/22 20:51:38 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "
# define IS_PIPE 301 // |
# define IP_REDIR 302 // <
# define OP_REDIR 303 // >
# define APPEND 304 // >>
# define HEREDOC 305 // <<

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../MY_LIB/ft_printf/ft_printf.h"
# include "../MY_LIB/ft_printf2/ft_printf2.h"
# include "../MY_LIB/get_next_line/get_next_line_bonus.h"

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
	struct s_list	*prev;
	struct s_msc	*msc;
	int				quote_status;
	int				token_status;
	int				id;
}			t_list;

typedef struct s_cmd
{
	char	*cmd;
	char	*option;
	char	**full_cmd;
	int		pid;
	int		fd_in;
	int		fd_in_type;
	int		fd_out;
	int		fd_out_type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_msc	*msc;
}				t_cmd;

typedef struct s_msc
{
	t_list	*lex;
	t_cmd	*cmd;
	bool	loop;
	char	*input;
	char	*env_user;
	char	*env_path;
	char	*env_cwd;
	char	*env_home;
	// char	*prompt_cwd;
	// char	*prompt;
	char	**env_cpy;
}				t_msc;

//global variable
extern int	g_sig_status;

//free_stuff.c
void	free_null(void **ptr);
void	ft_free_arr(char **strs);
void	free_structs(t_msc *msc);
void	free_all(t_msc *msc);

//error_handling.c
void	malloc_error_free_exit(t_msc *msc, char *to_free, char *to_free2);

//main.c
void	init_msc(t_msc *msc, char **env);
void	handle_input(t_msc *msc);

//dup_utils.c
int		ft_arrlen(char **str);
char	**ft_dup_arr(char **strs);

//signals.c
void	handle_sigint(int sig);

//exp_func.c
void	exp_head(t_msc *msc);
void	exp_logic_new(t_msc *msc, t_list *tmp);
void	exp_sub(t_list *tmp, int i, int aA0_end, t_msc *msc);
void	exp_tilde(t_msc *msc, t_list *tmp);
int		ft_shift_to_dollar(char *str, int reboot);
int		get_quote_status(char *str, int dol_i);

//exp_utils.c
char	*ft_strjoin_free(char *s1, char *s2, char *to_free, char *to_free2);
char	*free_two(char *to_free, char *to_free2);
int		ft_strchr_i(const char *s, int c);
int		ft_trimascii(char *str);
int		ft_is_whitespace(char *pos, int i);
int		ft_is_whitespace_str(char *str);

//op_func.c
void	tokenize_op(t_msc *msc);
void	rejoin_tokens(t_msc *msc);
void	reset_order(t_list *tmp);
void	tokenize_individual_op(t_msc *msc, t_list *tmp, char op);
int		ft_lst_insert(t_list *node, char *s, t_msc *msc);

//kill_quotes.c
void	kill_quotes(t_msc *msc);
void	kill_quote_str(t_msc *msc, t_list *tmp, char q);
int		jump_quotes(char *s, int i);

//pars_func.c
void	pars_head(t_msc *msc);
int		pars_list(t_msc *msc);
void	pars_init_cmd(t_msc *msc);

//list_utils1.c
t_list	*ft_lstnew(t_msc *ms, const char *s, int i);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
t_list	*init_lst(t_msc *msc, char **input);

//lex_funcs.c
void	free_2d_arr(char **arr);
void	input_lexer(t_msc *msc);
void	ft_printlist(t_list *lst); //ONLY FOR TESTING; DELETE FROM FINAL VERSION

//lex_utils1.c
int		quote_checker(const char *s);
void	skip_section(const char *s, int *i, int *wc, int id);
char	*set_word(const char *s, int *end, int start);
int		has_quotes(const char *s);
char	**set_array(const char *s, int wc);

//lex_utils2.c
int		search_estr(t_list *lst);
//int search_opipe(t_list *lst);
void	set_token_flag(t_list *lst);
int		is_operator(const char *s);
void	reset_lex_index(t_list *lst);
int		no_pipes(t_list *lst);

//lex_utils3.c
int		check_whs_betw_op(t_msc *msc, char op);
int		check_open_op(t_msc *msc);
int		consec_ops(t_msc *msc);
int		pipe_first(t_msc *msc);

//lex_split.c
int		isws(const char c);
void	*del_split(char **words, int i);
int		get_wc(const char *s);
char	*get_wd(const char *s, int *i);
char	**lex_split(char *s);

//cmd_utils1.c
t_cmd	*ft_cmdnew(t_msc *ms);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdclear(t_cmd **lst);
t_cmd	*init_cmd(t_msc *msc, int nb);

//cmd_utils2.c
int		nb_of_cmds(t_list *lst);
char	**cmd_setter(t_list *lst);
char	**get_full_cmd(t_list *lst, int start, int end);
char	**shorten_arr(char **ret, int len);
int		nb_of_estr(char **arr);
void	print2d(t_cmd *cmds);

//in_out_files.c
int	set_in_out_file(t_cmd *cmd);
void	ft_outfile(t_cmd *cmd, int i, int type);
void	ft_infile(t_cmd *cmd, int i, int type);

#endif
