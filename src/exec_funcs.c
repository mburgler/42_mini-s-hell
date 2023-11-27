/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:16:52 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 14:42:08 by abektimi         ###   ########.fr       */
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
	if (execve(path, cur_cmd, cur_env) == -1)
	{
		if (!path || !cur_cmd)
			g_sig_status = 127;
		free_exec_temps(path, NULL, cur_cmd, cur_env);
		perror("Error in executor()");
		strerror(errno);
		if (errno == EACCES)
			g_sig_status = 126;
		exit(g_sig_status);
	}
	return (0);
}

int	wait_and_analyze(t_msc *msc, pid_t *pid)
{
	int		i;
	int		status;
	pid_t	term_pid;
	t_cmd	*tmp;

	i = 0;
	tmp = msc->cmd;
	close_all(tmp);
	while (i < nb_of_processes(tmp))
	{
		term_pid = waitpid(pid[i], &status, WUNTRACED);
		if (term_pid == -1)
			free_msc_and_errno(msc, "Error in wait_and_analyze()");
		if (WIFEXITED(status))
			g_sig_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			set_sig_exit_status(status);
		else if (WIFSTOPPED(status))
			g_sig_status = WSTOPSIG(status);
		i++;
	}
	return (0);
}

//saves a copy of the previous command's output for later use by subsequent
//commands, and then calls wait_and_analyze()
int	main_process(t_cmd *cmd, int *pr_op)
{
	*pr_op = cmd->p_fds[0];
	if (close(cmd->p_fds[1]) == -1)
		return (-1);
	return (0);
}

//calls the executor() function inside a child process after
//setting up the file descriptors accordingly
int	process_cmd(t_cmd *cmd, t_env *env, int *pr_op)
{
	if (!cmd->cmd)
	{
		close(cmd->p_fds[0]);
		close(cmd->p_fds[1]);
		if (cmd->fd_in > STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out > STDOUT_FILENO)
			close(cmd->fd_out);
		exit(0);
	}
	if (set_file_desc(cmd, cmd->p_fds, pr_op) == -1)
		exit_child_and_errno("Child failed to set up fds");
	return (executor(cmd, env, is_builtin(cmd->cmd)));
}

//first part of the minishell executor; it creates child processes for all
//the commands of a pipeline which require one, and uses
//the pipe() syscall to establish inter-process communication
int	make_pipeline(t_msc *msc)
{
	int		prev_output;
	pid_t	*pid;
	t_cmd	*tmp;
	int		i;

	if (!msc || !msc->cmd)
		return (-1);
	tmp = msc->cmd;
	if (tmp->prev == NULL && tmp->next == NULL && is_no_op_builtin(tmp->cmd))
		return (exec_no_op_builtin(tmp));
	prev_output = 0;
	pid = malloc(sizeof(pid_t) * nb_of_processes(tmp));
	if (!pid)
		return (-1);
	i = 0;
	while (tmp)
	{
		if (pipe(tmp->p_fds) == -1)
			free_msc_and_errno(msc, "Error in make_pipeline()");
		pid[i] = fork();
		if (pid[i] == -1)
			free_msc_and_errno(msc, "Error in make_pipeline()");
		else if (pid[i] == 0)
			process_cmd(tmp, msc->dup_env, &prev_output);
		else if (pid[i] > 0)
			main_process(tmp, &prev_output);
		tmp = tmp->next;
		i++;
	}
	wait_and_analyze(msc, pid);
	free(pid);
	return (0);
}
