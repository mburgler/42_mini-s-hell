/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:06:21 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/05 17:49:21 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_echo_head(t_cmd *cmd)
{
	int	i;

	i = shift_to_print(cmd->full_cmd);
	if (i == 1)
	{
		while (cmd->full_cmd[i])
		{
			ft_printf("%s", cmd->full_cmd[i]);
			if (cmd->full_cmd[i + 1])
				ft_printf(" ");
			i++;
		}
		ft_printf("\n");
	}
	else
	{
		while (cmd->full_cmd[i])
		{
			ft_printf("%s", cmd->full_cmd[i]);
			if (cmd->full_cmd[i + 1])
				ft_printf(" ");
			i++;
		}
	}
}

int	shift_to_print(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i][0] != '-' || str[i][1] != 'n'|| no_n(str[i] + 1))
			break ;
		else
			i++;
	}
	return (i);
}

int	no_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == 'n')
		i++;
	if (i != (int)ft_strlen(str))
		return (1);
	return (0);
}