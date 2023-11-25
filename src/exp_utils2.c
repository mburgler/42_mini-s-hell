/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:41:39 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/14 17:46:14 by abektimi         ###   ########.fr       */
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
		if (str[i] == ' ' || str[i] == 9 || str[i] == 10
			|| str[i] == 11 || str[i] == 12 || str[i] == 13)
			return (i);
		i++;
	}
	return (-1);
}

void	exp_retokenize(t_msc *msc)
{
	t_list	*tmp;
	int		i;

	tmp = msc->lex;
	while (tmp)
	{
		if (tmp->exp == 1 && tmp->quote_status == 0)
		{
			i = ft_is_whitespace_str(tmp->str);
			exp_retokenize_inner(i, tmp, msc);
		}
		tmp = tmp->next;
	}
}

void	exp_retokenize_inner(int i, t_list *tmp, t_msc *msc)
{
	char	*buff;
	char	*to_free;

	if (i != -1)
	{
		to_free = tmp->str;
		tmp->str = ft_substr(tmp->str, 0, i);
		if (!tmp->str)
			malloc_error_free_exit(msc, NULL, NULL);
		while (to_free[i] && (to_free[i] == ' ' || to_free[i] == 9
				|| to_free[i] == 10 || to_free[i] == 11 || to_free[i] == 12
				|| to_free[i] == 13))
			i++;
		buff = ft_substr(to_free, i, ft_strlen(to_free) - i);
		if (!buff)
			malloc_error_free_exit(msc, to_free, NULL);
		free(to_free);
		if (!ft_lst_insert(tmp, buff, msc))
			malloc_error_free_exit(msc, NULL, NULL);
	}
}
