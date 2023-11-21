/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 05:24:27 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/18 17:17:21 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if a command is a builtin as per the minishell subject
int	is_builtin(const char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

//applies necessary changes to the full_cmd variable of a given 
//node of type t_cmd before passing full_cmd to execve()
char	**assemble_cmd(t_cmd *cmd)
{
	int		i;
	char	**ret;

	if (!cmd || !cmd->full_cmd)
		return (NULL);
	free(cmd->full_cmd[0]);
	cmd->full_cmd[0] = NULL;
	cmd->full_cmd[0] = ft_strdup(cmd->cmd);
	if (!cmd->full_cmd[0])
		return (NULL);
	i = 0;
	while (cmd->full_cmd[i])
		i++;
	if (i == 1 && cmd->fd_in_type == HEREDOC)
	{
		ret = malloc(sizeof(char *) * 3);
		ret[0] = ft_strdup(cmd->cmd);
		ret[1] = ft_strdup(cmd->heredoc_name);
		ret[2] = NULL;
		free_2d_arr(cmd->full_cmd);
		cmd->full_cmd = ret;
	}
	return (cmd->full_cmd);
}

//constructs an array of strings containing the env variables saved in
//the list of type t_env for later use by execve() in the executor() function
char	**assemble_env(t_env *env)
{
	int		i;
	char	**ret;
	t_env	*tmp;

	if (!env)
		return (NULL);
	i = 0;
	tmp = env;
	ret = malloc(sizeof(char *) * (nb_of_env_vars(tmp) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (env)
	{
		ret[i] = get_key_and_value(env->key, env->value);
		if (!ret[i])
			return (del_split(ret, i));
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

//counts the number of elements in the t_env list used by minishell
int	nb_of_env_vars(t_env *env)
{
	int	i;

	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

//returns a string containing an env variable's name 
//and value to assemble_env()
char	*get_key_and_value(const char *key, const char *value)
{
	char	*first_part;
	char	*ret;

	if (!key)
		return (NULL);
	first_part = ft_strjoin(key, "=");
	if (!first_part)
		return (NULL);
	if (value)
		ret = ft_strjoin(first_part, value);
	if (!value)
		ret = ft_strdup(first_part);
	if (!ret)
	{
		free(first_part);
		return (NULL);
	}
	free(first_part);
	return (ret);
}
