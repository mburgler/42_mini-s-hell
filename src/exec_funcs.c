/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:03:57 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/01 20:39:42 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//sets the cmd and option variables in each node of the list of type t_cmd
/*
NOTE TO SELF on ft_strdup: no need to remove whitespaces, because commands
such as wc, ls, and so on will reject flags if the respective string contains
anything other than the relevant characters upon calling execve()
(e.g: '   -l  ' is invalid input for wc)
*/
void	set_cmd_and_option(t_cmd *cmds)
{
	int		i;
	char	**cmd_and_opt;

	if (!cmds)
		return ;
	while (cmds)
	{
		cmd_and_opt = ft_split(cmds->full_cmd[0], ' ');
		i = 0;
		while (cmd_and_opt[i] != NULL)
			i++;
		if (i == 1)
		{
			cmds->cmd = ft_strdup(cmd_and_opt[0]);
			if (is_option(cmds->full_cmd[1]))
				cmds->option = ft_strdup(cmds->full_cmd[1]);
		}
		else if (i == 2)
		{
			cmds->cmd = ft_strdup(cmd_and_opt[0]);
			cmds->option = ft_strdup(cmd_and_opt[1]);
		}
		free_2d_arr(cmd_and_opt);
		cmds = cmds->next;
	}
}

//supposed to execute commands the way they've been formulated in
//the functions prep_parent() and prep_child()
//void	executor();

//preps the parameters of the parent process for passing on to executer()
void	prep_parent(t_cmd *cmd, int *p_fds, t_env *env)
{
	//int	fd;
	(void)cmd;
	(void)p_fds;
	(void)env;

	printf("Parent: I'm the parent\n");
	//1. check for builtins and execute if necessary;
	//2. otherwise use dup2 to adjust file descriptors, check for return == -1
	//3. close unused file descriptor of pipe
	//4. call executor function
}

//preps the parameters of the child process for passing on to executer()
void	prep_child(t_cmd *cmd, int *p_fds, t_env *env)
{
	//int	fd;
	(void)cmd;
	(void)p_fds;
	(void)env;

	printf("Child: I'm the child\n");
	//1. check for builtins and execute if necessary;
	//2. otherwise use dup2 to adjust file descriptors, check for return == -1
	//3. close unused file descriptor of pipe
	//4. call executor function
}

//This function is supposed to create a pipeline consisting of the cmds
//formulated in the list msc->cmd and its nodes
void	make_pipeline(t_msc *msc)
{
	int		p_fds[2];
	pid_t	pid;
	t_cmd	*tmp;

	if (!msc->cmd)
		return ;
	tmp = msc->cmd;
	while (tmp->next)
	{
		if (pipe(p_fds) == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		pid = fork();
		if (pid == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		else if (pid == 0)
			prep_child(tmp->next, p_fds, msc->env_cpy);
		else if (pid > 0)
			prep_parent(tmp, p_fds, msc->env_cpy);
		tmp = tmp->next;
	}
}
