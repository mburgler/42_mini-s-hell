/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:38:26 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 14:34:47 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//frees memory taken up by the temporary variables in executor()
//or find_cmd_path() if a malloc() error occurs
void	*free_exec_temps(char *del1, char *del2, char **del3, char **del4)
{
	if (del1 != NULL)
	{
		free(del1);
		del1 = NULL;
	}
	if (del2 != NULL)
	{
		free(del2);
		del2 = NULL;
	}
	if (del3 != NULL)
	{
		free_2d_arr(del3);
		del3 = NULL;
	}
	if (del4 != NULL)
	{
		free_2d_arr(del4);
		del4 = NULL;
	}
	return (NULL);
}

//creates an array of strings, which contains all the directories
//listed in the env variable PATH
char	**get_dirs(t_env *env)
{
	char	**ret;

	if (!env)
		return (NULL);
	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	ret = ft_split(env->value, ':');
	if (!ret)
		return (NULL);
	return (ret);
}

//returns the full path to an executable for later use by
//execve() in the executor() function
char	*find_cmd_path(char *const cmd[], t_env *env)
{
	int		i;
	char	**dirs;
	char	*path;
	char	*full_path;

	dirs = get_dirs(env);
	if (!cmd || !env || !dirs)
		return (NULL);
	i = -1;
	while (dirs[++i])
	{
		path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(path, cmd[0]);
		if (!path || !full_path)
			return (free_exec_temps(path, full_path, dirs, NULL));
		free(path);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_2d_arr(dirs);
			return (full_path);
		}
		free(full_path);
	}
	free_2d_arr(dirs);
	return (NULL);
}

//calls the required function depending on the builtin
int	exec_builtin(t_cmd *cmd)
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
	free_all(cmd->msc);
	exit(0);
}

int	nb_of_processes(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
