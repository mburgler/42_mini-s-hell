/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:38:31 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/19 21:13:20 by mburgler         ###   ########.fr       */
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
	char	*to_free;
	int	i;
	int	j;

	i = 0;
	j = 0;
	to_free = tmp->str;
	buff = calloc(ft_strlen(tmp->str) + 1, sizeof(char));
	if (!buff)
		malloc_error_free_exit(msc, NULL, NULL);
	while (tmp->str[i])
	{
		if (tmp->str[i] == q)
			i++;
		else
		{
			buff[j] = tmp->str[i];
			i++;
			j++;
		}
	}
	buff[j] = '\0';
	tmp->str = buff;
	free(to_free);
}
