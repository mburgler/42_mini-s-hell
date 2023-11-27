/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:15:34 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 17:27:21 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	num_only(const char *str)
{
	int		i;

	i = 0;
	while (str[i] && isws(str[i]))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] != '\0' && !isws(str[i]))
		return (0);
	while (str[i])
	{
		if (!isws(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit_head(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->full_cmd)
		return ;
	i = 0;
	while (cmd->full_cmd[i] != NULL)
		i++;
	if (i == 1)
		exit(g_sig_status);
	else if (i > 2)
		exit(127);
	else if (i == 2)
	{
		if (!num_only(cmd->full_cmd[1]))
			exit(2);
		exit(ft_atoi(cmd->full_cmd[1]));
	}
}
