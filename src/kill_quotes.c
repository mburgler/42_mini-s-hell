/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:06:02 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/23 20:10:32 by mburgler         ###   ########.fr       */
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
		// if(tmp->str[0] == '\"' || tmp->str[0] == '\'')
		// 	tmp->quote_first_pos = 1;
		// else
		// 	tmp->quote_first_pos = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '\'')
			{
				kill_quote_str(msc, tmp, '\'');
				break ;
			}
			if(tmp->str[i] == '\"')
			{
				kill_quote_str(msc, tmp, '\"');
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
	buff = calloc(ft_strlen(tmp->str) - 1, sizeof(char));
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

int	jump_quotes(char *s, int i)
{
	if (s[i] == '\"')
	{
		i++;
		while (s[i] && s[i] != '\"')
			i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	return (i);
}
