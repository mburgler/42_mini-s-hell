/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:16:52 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/14 17:24:03 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//creates the variables which must be passed as parameters to execve() and
//processes commands that way, if the command is not a builtin
int	executor(t_cmd *cmd, t_env *env, int cmd_type)
{
	char	*path;
	char	**cur_cmd;
	char	**cur_env;

	if (!cmd || !env)
		return (-1);
	if (cmd_type == 1)
		return (exec_builtin(cmd));
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

//waits for a specified child process to end and analyzes its exit status
int	wait_and_analyze(t_msc *msc, pid_t pid)
{
	int		status;
	pid_t	term_pid;

	term_pid = waitpid(pid, &status, WUNTRACED);
	if (term_pid == -1)
		free_msc_and_errno(msc, "Error in wait_and_analyze(): ");
	if (WIFEXITED(status))
		g_sig_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
		{
			perror("Segmentation fault (core dumped)\n");
			g_sig_status = 139;
		}
		else
			g_sig_status = WTERMSIG(status);
	}
	else if (WIFSTOPPED(status))
		g_sig_status = WSTOPSIG(status);
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
	wait_and_analyze(msc, pid);
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
int	make_pipeline(t_msc *msc)
{
	int		p_fds[2];
	int		prev_output;
	pid_t	pid;
	t_cmd	*tmp;

	if (!msc || !msc->cmd)
		return (-1);
	tmp = msc->cmd;
	if (tmp->prev == NULL && tmp->next == NULL && is_builtin(tmp->cmd))
		return (exec_single_builtin(tmp));
	prev_output = 0;
	while (tmp)
	{
		if (pipe(p_fds) == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		pid = fork();
		if (pid == -1)
			free_msc_and_errno(msc, "Error in make_pipeline(): ");
		else if (pid == 0)
			process_cmd(tmp, msc->dup_env, p_fds, &prev_output);
		else if (pid > 0)
			main_process(msc, pid, p_fds, &prev_output);
		tmp = tmp->next;
	}
	return (0);
}
