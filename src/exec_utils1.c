/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 05:24:27 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/11 15:24:41 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if a string passed to it qualifies as an optional flag for a shell cmd
int	is_option(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && isws(str[i]))
		i++;
	if (str[i] == '-')
		return (1);
	return (0);
}

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
	return (0);
}

//constructs an array of strings containing the cmd and option values of
//t_cmd *cmd for later use by execve() in the eexecutor() function
// char	**assemble_cmd(t_cmd *cmd)
// {
// 	int		i;
// 	char	**ret;

// 	if (cmd->cmd == NULL)
// 		return (NULL);
// 	i = 1;
// 	if (cmd->cmd != NULL && cmd->option != NULL)
// 		i++;
// 	ret = malloc(sizeof(char *) * (i + 1));
// 	if (!ret)
// 		return (NULL);
// 	if (i == 1)
// 	{
// 		ret[0] = ft_strdup(cmd->cmd);
// 		ret[1] = NULL;
// 	}
// 	else if (i == 2)
// 	{
// 		ret[0] = ft_strdup(cmd->cmd);
// 		ret[1] = ft_strdup(cmd->option);
// 		ret[2] = NULL;
// 	}
// 	return (ret);
// }

char	**assemble_cmd(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**ret;

	if (cmd->cmd == NULL)
		return (NULL);
	i = 0;
	if (cmd->option != NULL)
		while (cmd->option[i] != NULL)
			i++;
	ret = malloc(sizeof(char *) * (i + 1 + 1));
	if (!ret)
		return (NULL);
	if (i == 0)
	{
		ret[0] = ft_strdup(cmd->cmd);
		ret[1] = NULL;
	}
	if (i > 0)
	{
		ret[0] = ft_strdup(cmd->cmd);
		j = 1;
		while (cmd->option[j - 1])
		{
			ret[j] = ft_strdup(cmd->option[j - 1]);
			j++;
		}
		ret[j] = NULL;
	}
	return (ret);
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
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	ret = malloc(sizeof(char *) * (i + 1)); //add int variable to the t_env list to save lines here
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
