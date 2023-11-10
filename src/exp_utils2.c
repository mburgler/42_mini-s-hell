/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:41:39 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/10 16:42:49 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_shift_to_dollar(char *str, int reboot)
{
	static int	i;

	if (reboot == 1)
	{
		i = 0;
		return (-42);
	}
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != '\"')
		{
			if (ft_is_whitespace(str, i + 1) == -1)
			{
				i++;
				return (i - 1);
			}
		}
		i++;
	}
	return (-1);
}

int	get_quote_status(char *str, int dol_i)
{
	int	i;

	i = 0;
	while (str[i] && i < dol_i)
	{
		if (str[i] == '\"')
			return (2);
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && i < dol_i)
			{
				if (str[i] == '\'')
					return (0);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_whitespace_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == ' ' && str[i] == 9 && str[i] == 10 &&
			str[i] == 11 && str[i] == 12 && str[i] == 13)
			return (i);
		i++;
	}
	return (-1);
}
