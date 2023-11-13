/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:16:52 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/13 17:07:10 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	executor(t_cmd *cmd, t_env *env, int cmd_type)
{
	char	*path;
	char	**cur_cmd;
	char	**cur_env;

	if (!cmd || !env)
		return (-1);
	if (cmd_type == 1)
		return (exec_builtin(cmd, env));
	path = NULL;
	cur_cmd = NULL;
	cur_env = NULL;
	set_exec_temps(&cmd, &path, &cur_cmd, &cur_env);
	if (!cur_cmd || !cur_env || !path)
	{
		free_exec_temps(path, NULL, NULL, cur_env);
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

	waitpid(pid, &status, WUNTRACED);
	if (!WIFEXITED(status))
	{
		if (WIFSIGNALED(status))
			printf("\nCHILD TERMINATED BY SIGNAL\n");
		else if (WIFSTOPPED(status))
			printf("\nCHILD STOPPED BY SIGNAL\n");
	}
	return (0);
}

//saves a copy of the previous command's output for later use by subsequent
//commands, and then calls wait_and_analyze()
int	main_process(t_msc *msc, pid_t pid, int *p_fds, int *pr_op)
{
	(void)msc;
	if (close(p_fds[1]) == -1)
		return (-1);
	*pr_op = p_fds[0];
	wait_and_analyze(pid);
	return (0);
}

//calls the executor() function inside a child process after
//setting up the file descriptors accordingly
int	process_cmd(t_cmd *cmd, t_env *env, int *p_fds, int *pr_op)
{
	if (cmd->prev == NULL && cmd->next == NULL)
	{
		if (close(p_fds[0]) == -1 || close(p_fds[1]) == -1
			|| set_redir(cmd, p_fds, pr_op))
			return (-1);
		return (executor(cmd, env, is_builtin(cmd->cmd)));
	}
	set_file_desc(cmd, p_fds, pr_op);
	return (executor(cmd, env, is_builtin(cmd->cmd)));
}

//first part of the minishell executor; it creates child processes for all
//the commands of a pipeline which require one, and uses
//the pipe() syscall to establish inter-process communication
void	make_pipeline(t_msc *msc)
{
	int		i;
	int		p_fds[2];
	int		prev_output;
	pid_t	*pids;
	t_cmd	*tmp;

	if (!msc || !msc->cmd)
		return ;
	tmp = msc->cmd;
	if (tmp->prev == NULL && tmp->next == NULL && is_builtin(tmp->cmd))
	{
		exec_single_builtin(tmp, msc->dup_env);
		return ;
	}
	pids = malloc(sizeof(pid_t) * nb_of_processes(tmp));
	if (!pids)
		free_msc_and_errno(msc, "Error in make_pipeline(): ");
	i = 0;
	prev_output = 0;
	while (tmp)
	{
		if (pipe(p_fds) == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		pids[i] = fork();
		if (pids[i] == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		else if (pids[i] == 0)
			process_cmd(tmp, msc->dup_env, p_fds, &prev_output);
		else if (pids[i] > 0)
			main_process(msc, pids[i], p_fds, &prev_output);
		tmp = tmp->next;
		i++;
	}
	free(pids);
}
