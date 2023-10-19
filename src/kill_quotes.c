/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:38:31 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/19 20:46:13 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kill_quotes(t_msc *msc)
{
	t_list	*tmp;
	int		i;

	tmp = msc->lex;
	while (tmp && tmp->str)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '\'')
			{
				kill_quote_str(msc, tmp, '\'')
				break ;
			}
			if(tmp->str[i] == '\"')
			{
				kill_quote_str(msc, tmp, '\"')
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	kill_quote_str(t_msc *msc, t_list *tmp, char q)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff = tmp->str;
	while (tmp->str[i])
	{
		if (tmp->str[i] == q)
			i++;
		else
		{
			tmp->str[j] = tmp->str[i];
			i++;
			j++;
		}
	}
	tmp->str[j] = '\0';
	if (tmp->str[0] == '\0')
	{
		free(tmp->str);
		tmp->str = NULL;
	}
	free(buff);
}
