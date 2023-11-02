/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:03:57 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/02 02:05:15 by abektimi         ###   ########.fr       */
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
		while (cmd_and_opt && cmd_and_opt[i] != NULL)
			i++;
		if (i == 1)
		{
			cmds->cmd = ft_strdup(cmd_and_opt[0]);
			if (cmds->full_cmd[1] != NULL && (cmds->full_cmd[1]))
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
	(void)env;

	printf("Parent: I'm the parent\n");
	if (close(p_fds[1]) == -1)
		free_msc_and_errno(cmd->msc, "Error in prep_parent(): ");
	if (dup2(cmd->next->fd_out, 1) == -1 || dup2(p_fds[0], 0) == -1)
		free_msc_and_errno(cmd->msc, "Error in prep_parent(): ");
	// if (is_builtin(cmd->cmd))
	// 	executor(cmd, p_fds, env, 1);
	if (!is_builtin(cmd->cmd))
		printf("\nParent: Received cmd is not a builtin\n");
	//3. close unused file descriptor of pipe
	//4. call executor function
}

//preps the parameters of the child process for passing on to executer()
void	prep_child(t_cmd *cmd, int *p_fds, t_env *env)
{
	(void)env;

	printf("Child: I'm the child\n");
	if (close(p_fds[0]) == -1)
		free_msc_and_errno(cmd->msc, "Error in prep_child(): ");
	if (dup2(cmd->prev->fd_in, 0) == -1 || dup2(p_fds[1], 1) == -1)
		free_msc_and_errno(cmd->msc, "Error in prep_child(): ");
	// if (is_builtin(cmd->cmd))
	// 	executor(cmd, p_fds, env, 1);
	if (!is_builtin(cmd->cmd))
		printf("\nChild: Received cmd is not a builtin\n");
	//3. close unused file descriptor of pipe
	//4. call executor function
	exit(0);
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
			prep_child(tmp->next, p_fds, msc->dup_env);
		else if (pid > 0)
			prep_parent(tmp, p_fds, msc->dup_env);
		tmp = tmp->next;
	}
}
