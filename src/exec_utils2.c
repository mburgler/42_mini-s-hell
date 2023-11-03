/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:38:26 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/03 16:29:47 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//frees memory taken up by the temporary variables in executor()
//or find_cmd_path() if a malloc() error occurs
void	*free_exec_temps(char *del1, char *del2, char **del3, char **del4)
{
	if (del1 != NULL)
		free(del1);
	if (del2 != NULL)
		free(del2);
	if (del3 != NULL)
		free_2d_arr(del3);
	if (del4 != NULL)
		free_2d_arr(del4);
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
