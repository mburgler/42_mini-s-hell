/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:50:24 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 14:49:28 by mburgler         ###   ########.fr       */
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
		if (((cur >= IP_REDIR && cur <= HEREDOC) && (nxt >= IP_REDIR
					&& nxt <= HEREDOC)) || (cur == IS_PIPE && nxt == IS_PIPE))
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
	int		i;
	char	*tmp;

	i = 0;
	tmp = msc->input;
	if (!msc || !tmp)
		return (0);
	while (tmp[i])
	{
		while (tmp[i] != op && tmp[i])
			i++;
		if (tmp[i])
			i++;
		while (tmp[i] && (tmp[i] == ' ' || tmp[i] == 9 || tmp[i] == 10
				|| tmp[i] == 11 || tmp[i] == 12 || tmp[i] == 13))
			i++;
		if (tmp[i] && tmp[i] == op && tmp[i - 1] != op && op_no_quotes(tmp, i))
			return (1);
	}
	return (0);
}

int	op_no_quotes(char *tmp, int op_pos)
{
	int	i;
	int	quote_status;

	i = 0;
	quote_status = 0;
	while (i <= op_pos)
	{
		if (tmp[i] == '\"' && quote_status == 0)
			quote_status = 2;
		else if (tmp[i] == '\'' && quote_status == 0)
			quote_status = 1;
		else if (tmp[i] == '\"' && quote_status == 2)
			quote_status = 0;
		else if (tmp[i] == '\'' && quote_status == 1)
			quote_status = 0;
		i++;
	}
	if (quote_status != 0)
		return (0);
	else
		return (1);
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
