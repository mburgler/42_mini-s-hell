/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:50:24 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/22 23:10:06 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//after operators get tokenized, consec_ops() determines if any of them appear
//immediately one after another, in which case the function returns 1

int	consec_ops(t_msc *msc)
{
	int		cur;
	int		nxt;
	t_list	*tmp;

	if (!msc->lex)
		return (0);
	if (check_whs_betw_op(msc, '<') || check_whs_betw_op(msc, '>'))
	{
		g_sig_status = 258;
		return (1);
	}
	tmp = msc->lex;
	while (tmp->next != NULL)
	{
		cur = tmp->token_status;
		nxt = tmp->next->token_status;
		if ((cur >= IS_PIPE && cur <= HEREDOC) 
			&& (nxt >= IS_PIPE && nxt <= HEREDOC))
		{
			g_sig_status = 258;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_whs_betw_op(t_msc *msc, char op)
{
	int i;
	char *tmp;

	i = 0;
	tmp = msc->input;
	if (!msc || !tmp)
		return (0);
	while (tmp[i])
	{
		while (tmp[i] != op && tmp[i])
			i++;
		i++;
		while (tmp[i] && (tmp[i] == ' ' || tmp[i] == 9 || tmp[i] == 10
			|| tmp[i] == 11 || tmp[i] == 12 || tmp[i] == 13))
			i++;
		if (tmp[i] && tmp[i] == op && tmp[i - 1] != op)
			return (1);
	}
	return (0);
}

int	check_open_op(t_msc *msc)
{
	t_list	*tmp;

	if (!msc->lex)
		return (0);
	tmp = ft_lstlast(msc->lex);
	if (tmp->token_status != 0)
	{
		g_sig_status = 258;
		return (1);
	}
	return (0);
}

int	pipe_first(t_msc *msc)
{
	t_list	*tmp;

	if (!msc->lex)
		return (0);
	tmp = msc->lex;
	if (tmp->token_status == IS_PIPE)
	{
		g_sig_status = 258;
		return (1);
	}
	return (0);
}
