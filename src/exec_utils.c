/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 05:24:27 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/01 22:39:10 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
