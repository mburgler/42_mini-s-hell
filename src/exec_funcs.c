/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:16:52 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/07 23:49:23 by abektimi         ###   ########.fr       */
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
			if (cmds->full_cmd[1] != NULL && is_option(cmds->full_cmd[1]))
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

int	executor(t_cmd *cmd, t_env *env, int cmd_type)
{
	char	*path;
	char	**cur_cmd;
	char	**cur_env;

	if (!cmd || !env)
		return (-1);
	if (cmd_type == 1)
		return (exec_builtin(cmd, env));
	printf("\nEXECUTOR REACHED\n");
	cur_cmd = assemble_cmd(cmd);
	cur_env = assemble_env(env);
	path = find_cmd_path(cur_cmd, env);
	if (!path || !cur_cmd || !cur_env)
	{
		free_exec_temps(path, NULL, cur_cmd, cur_env);
		free_msc_and_errno(cmd->msc, "Error in executor(): ");
	}
	if (execve(path, cur_cmd, cur_env) == -1)
	{
		free_exec_temps(path, NULL, cur_cmd, cur_env);
		return (-1);
	}
	return (0);
}

int	wait_and_analyze(pid_t pid)
{
	int	status;

	printf("\nANALYSIS REACHED\n");
	waitpid(pid, &status, WUNTRACED);
	printf("\nCHILD PROCESS DONE\n");
	if (!WIFEXITED(status))
	{
		if (WIFSIGNALED(status))
			printf("\nCHILD TERMINATED BY SIGNAL\n");
		else if (WIFSTOPPED(status))
			printf("\nCHILD STOPPED BY SIGNAL\n");
	}
	return (0);
}

int	process_cmd(t_cmd *cmd, t_env *env, int *cur_fds, int *prev_fds)
{
	if (cmd->prev == NULL && cmd->next == NULL)
	{
		if (close(cur_fds[0]) == -1 || close(cur_fds[1]) == -1)
			return (-1);
		return (executor(cmd, env, is_builtin(cmd->cmd)));
	}
	set_file_desc(cmd, cur_fds, prev_fds);
	return (executor(cmd, env, is_builtin(cmd->cmd)));
}

void	make_pipeline(t_msc *msc)
{
	int		prev_fds[2];
	int		cur_fds[2];
	pid_t	pid;
	t_cmd	*tmp;

	if (!msc || !msc->cmd)
		return ;
	tmp = msc->cmd;
	while (tmp)
	{
		printf("\nTEST\n");
		if (tmp->prev != NULL)
			connect_fds(cur_fds[0], cur_fds[1], &prev_fds[0], &prev_fds[1]);
		if (pipe(cur_fds) == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		pid = fork();
		if (pid == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		else if (pid == 0)
			process_cmd(tmp, msc->dup_env, cur_fds, prev_fds);
		else if (pid > 0)
			wait_and_analyze(pid);
		close_all(tmp, cur_fds, prev_fds);
		tmp = tmp->next;
	}
}
