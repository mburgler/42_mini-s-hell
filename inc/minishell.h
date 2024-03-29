/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:39:55 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/28 20:19:14 by mburgler         ###   ########.fr       */
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
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../MY_LIB/ft_printf/ft_printf.h"
# include "../MY_LIB/ft_printf2/ft_printf2.h"
# include "../MY_LIB/get_next_line/get_next_line_bonus.h"

typedef struct s_list
{
	char			*str;
	int				quote_status;
	int				token_status;
	int				quote_first_pos;
	int				exp;
	int				id;
	struct s_list	*next;
	struct s_list	*prev;
	struct s_msc	*msc;
}			t_list;

//exp = 0: not expanded; exp = 1: expanded; exp = 2: expanded with op

typedef struct s_cmd
{
	char			*cmd;
	char			**option;
	char			**full_cmd;
	int				pid;
	int				index;
	int				fd_in;
	int				fd_in_type;
	int				fd_out;
	int				fd_out_type;
	int				p_fds[2];
	char			*heredoc_name;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_msc	*msc;
}				t_cmd;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
	struct s_msc	*msc;

}				t_env;

typedef struct s_exp
{
	char	*env;
	char	*beg;
	char	*end;
	char	*buff;
}				t_exp;

typedef struct s_msc
{
	t_list	*lex;
	t_cmd	*cmd;
	bool	loop;
	char	*input;
	char	*env_home;
	int		stop_file_error;
	char	*str_file_error;
	t_env	*dup_env;
}				t_msc;

//global variable
extern int	g_sig_status;

//free_stuff.c
void	ft_free_arr(char **strs);
void	free_structs_and_input(t_msc *msc);
void	free_all(t_msc *msc);
void	free_msc_and_exit_success(t_msc *msc);
void	main_free(t_msc *msc);

//error_handling.c
void	malloc_error_free_exit(t_msc *msc, char *to_free, char *to_free2);
void	free_msc_and_exit(t_msc *msc, char *msg);
void	free_msc_and_errno(t_msc *msc, char *msg);
void	exit_child_and_errno(char *msg);
void	exit_child_eacces(t_cmd *cmd, char *path, char **c_cmd, char **c_env);

//main.c
t_msc	*init_msc(char **env);
void	handle_input(t_msc *msc);
int		no_chars(const char *str);
void	ft_print2d(char **strs); //ONLY FOR TESTING; DELETE FROM FINAL VERSION

//env_dup.c
void	dup_env_head(t_msc *msc, char **org_env);
t_env	*ft_dup_envnew(char *str, t_msc *msc);
void	dup_env_error(t_msc *msc, t_env *current_node);
char	*ft_getenv(char *searchterm, t_msc *msc);

//env_utils.c
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envlast(t_env *lst);
void	ft_envclear(t_env **lst);
int		ft_strcmp(const char *s1, const char *s2);

//env_utils2.c
void	sh_lvl(t_msc *msc);
int		sh_lvl_irregular(t_msc *msc, t_env *tmp);
int		sh_lvl_alph(t_msc *msc, t_env *tmp);
int		sh_lvl_overflow(const char *str);

//signals.c
//signal.c
void	handle_sigint(int sig);
void	handle_sigint_parent(int sig);
void	quit_child(int sig);
void	perror_and_or_set_eacces(void);

//exp_func.c
void	exp_head(t_msc *msc);
char	*exp_logic_new(t_msc *msc, char *str, t_list *tmp);
char	*exp_sub(char *str, int i, int a0, t_msc *msc);
char	*exp_dol_qmark(t_msc *msc, char *str, int i);
void	exp_tilde(t_msc *msc, t_list *tmp);
int		ft_shift_to_dollar(char *str, int reboot);
int		get_quote_status(char *str, int dol_i);

//exp_utils1.c && exp_utils2.c && eexp_utils3.c
char	*ft_strjoin_free(char *s1, char *s2, char *to_free, char *to_free2);
char	*free_two(char *to_free, char *to_free2);
int		ft_strchr_i(const char *s, int c);
int		ft_trimascii(char *str);
int		ft_is_whitespace(char *pos, int i);
int		ft_is_whitespace_str(char *str);
void	exp_retokenize(t_msc *msc);
void	exp_retokenize_inner(int i, t_list *tmp, t_msc *msc);
t_exp	*exp_sub_init(char *str, int i, int a0, t_msc *msc);
void	malloc_error_free_exp_exit(t_msc *msc, t_exp *exp, char *tf, char *tf2);

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

//list_utils1.c
t_list	*ft_lstnew(t_msc *ms, const char *s, int i);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
t_list	*init_lst(t_msc *msc, char **input);

//lex_funcs.c
void	free_2d_arr(char ***arr);
int		check_syntax(t_msc *msc);
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
int		is_operator_str(const char *s);
void	reset_lex_index(t_list *lst);

//lex_utils3.c
int		check_whs_betw_op(t_msc *msc, char op);
int		op_no_quotes(char *tmp, int op_pos);
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
t_cmd	*ft_cmdnew(t_msc *ms, int i);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmdlast(t_cmd *lst);
t_cmd	*init_cmd(t_msc *msc, int nb);

//cmd_utils2.c
int		nb_of_cmds(t_list *lst);
char	**cmd_setter(t_list *lst);
char	**get_full_cmd(t_list *lst, int start, int end);
char	**shorten_arr(char **ret, int len);
int		nb_of_estr(char **arr);

//cmd_utils3.c
void	ft_cmdclear(t_cmd **lst);
void	kill_heredoc(t_cmd **lst);
int		no_pipes(t_list *lst);
void	printcmds(t_cmd *cmds); //ONLY FOR TESTING PURPOSES

//in_out_files.c
int		set_in_out_file(t_cmd *cmd);
void	ft_outfile(t_cmd *cmd, int i, int type);
void	ft_infile(t_cmd *cmd, int i, int type);
void	kill_in_out_file(t_cmd *cmd);
int		handle_heredoc(t_cmd *cmd, int i);

//in_out_files2.c
t_list	*shift_lex_for_cmd(t_cmd *cmd, t_list *tmp);
char	*bootstrap_exp_heredoc(char *buff, t_msc *msc);
char	*kill_quote_heredoc(t_msc *msc, char *str);
void	kill_in_out_file(t_cmd *cmd);
int		heredoc_break_loop(char *buff, t_cmd *cmd, int i);

//exec_prep.c
void	set_c_and_o(t_cmd *cmds);
void	isolate_cmd(t_cmd **cmd);

//exec_funcs.c
int		executor(t_cmd *cmd, t_env *env, int cmd_type);
int		wait_and_analyze(t_msc *msc, pid_t *pid);
int		main_process(t_cmd *cmd, int *pr_op);
int		process_cmd(t_cmd *cmd, t_env *env, int *prev_output);
int		make_pipeline(t_msc *msc);

//exec_extras.c
void	fork_loop(t_msc *msc, t_cmd *tmp, int *prev_output, pid_t **pid);
char	**append_heredoc_name(t_cmd **cmd);
void	fork_and_wait(t_msc *msc, t_cmd *tmp, int *pr_op, pid_t **pid);

//exec_utils1.c
int		is_builtin(const char *str);
char	**assemble_cmd(t_cmd *cmd);
char	**assemble_env(t_env *env);
int		nb_of_env_vars(t_env *env);
char	*get_key_and_value(const char *key, const char *value);

//exec_utils2.c
void	*free_exec_temps(char *del1, char *del2, char **del3, char **del4);
char	**get_dirs(t_env *env);
char	*find_cmd_path(char *const cmd[], t_env *env);
int		exec_builtin(t_cmd *cmd);
int		nb_of_processes(t_cmd *cmd);

//exec_utils3.c
void	set_exec_temps(t_cmd **cmd, char **path, char ***c_cmd, char ***c_env);
int		exec_single_builtin(t_cmd *cmd);
int		is_no_op_builtin(const char *cmd);
int		exec_no_op_builtin(t_cmd *cmd);
void	set_sig_exit_status(int wstatus);

//set_fds.c
int		close_single_fds(t_cmd *cmd);
int		set_file_desc(t_cmd *cmd, int *p_fds, int *pr_op);
void	close_all(t_cmd *cmds);
int		set_prev_output(int *pr_op);

//BUILTINS
//builtin_env.c
void	builtin_env(t_msc *msc);

//builtin_export.c
void	builtin_export_head(t_msc *msc, t_cmd *cmd);
void	export_core(t_msc *msc, char *str);
void	export_new(t_msc *msc, char *str);
void	export_known(t_msc *msc, char *str, t_env *node);
t_env	*check_if_known_var(t_msc *msc, char *str);
int		check_export_syntax(char *str);
char	*remove_plus(char *str);

int		check_export_syntax(char *str);
//builtin_unset.c
void	builtin_unset_head(t_msc *msc, t_cmd *cmd);
void	unset_core(t_msc *msc, char *str);
void	unset_indiv_node(t_msc *msc, t_env *node);

//builtin_echo_head.c
void	builtin_echo_head(t_cmd *cmd);
int		shift_to_print(char **str);
int		no_n(char *str);

//builtin_pwd.c
void	builtin_pwd_head(void);

//builtin_cd.c
void	builtin_cd_head(t_cmd *cmd);
char	*set_path(t_cmd *cmd);

//builtin_exit.c
int		num_only(const char *str);
void	builtin_exit_head(t_cmd *cmd);
void	exit_with_two_args(t_cmd *cmd);

//check_path_errors.c
int		no_valid_path(t_msc *msc);
int		is_empty_arg(const char *input);
int		erroneous_input(void);
void	kill_in_out_file_sub(t_cmd *cmd);

#endif
