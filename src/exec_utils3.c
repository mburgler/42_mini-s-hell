/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:26:23 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/11 22:36:10 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//sets the content of the three variables needed by the executor() function
void	set_exec_temps(t_cmd **cmd, char **path, char ***c_cmd, char ***c_env)
{
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
int	exec_single_builtin(t_cmd *cmd, t_env *env)
{
	(void)env;
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
	return (0);
}