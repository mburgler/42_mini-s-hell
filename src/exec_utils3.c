/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:26:23 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 23:28:52 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//sets the content of the three variables needed by the executor() function
void	set_exec_temps(t_cmd **cmd, char **path, char ***c_cmd, char ***c_env)
{
	if (!(*cmd))
		return ;
	if (access((*cmd)->cmd, F_OK | X_OK) == 0)
	{
		*path = ft_strdup((*cmd)->cmd);
		isolate_cmd(cmd);
		*c_cmd = assemble_cmd((*cmd));
	}
	else
	{
		*c_cmd = assemble_cmd((*cmd));
		*path = find_cmd_path(*c_cmd, (*cmd)->msc->dup_env);
	}
	*c_env = assemble_env((*cmd)->msc->dup_env);
}

//executes a builtin when its a standalone command
int	exec_single_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		builtin_echo_head(cmd);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		builtin_cd_head(cmd);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		builtin_pwd_head();
	if (ft_strcmp(cmd->cmd, "export") == 0)
		builtin_export_head(cmd->msc, cmd);
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		builtin_unset_head(cmd->msc, cmd);
	if (ft_strcmp(cmd->cmd, "env") == 0)
		builtin_env(cmd->msc);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		builtin_exit_head(cmd);
	return (0);
}

int	is_no_op_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_no_op_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		builtin_cd_head(cmd);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		builtin_pwd_head();
	if (ft_strcmp(cmd->cmd, "export") == 0)
		builtin_export_head(cmd->msc, cmd);
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		builtin_unset_head(cmd->msc, cmd);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		builtin_exit_head(cmd);
	return (0);
}

//sets the g_sig_status variable to the corresponding exit status in
//the case that WIFSIGNALED(status) is true
void	set_sig_exit_status(int wstatus)
{
	if (!WCOREDUMP(wstatus))
		g_sig_status = 128 + WTERMSIG(wstatus);
	else
	{
		g_sig_status = 139;
		write(2, "CHILD PROCESS encountered segmentation fault\n", 45);
	}
}
