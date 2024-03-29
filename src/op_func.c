/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 00:31:09 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/25 17:56:19 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//hey>du>>burli

void	tokenize_op(t_msc *msc)
{
	t_list	*tmp;

	tmp = msc->lex;
	while (tmp && tmp->str)
	{
		if (tmp->exp == 0)
		{
			tokenize_individual_op(msc, tmp, '|');
			tokenize_individual_op(msc, tmp, '>');
			tokenize_individual_op(msc, tmp, '<');
		}
		tmp = tmp->next;
	}
	rejoin_tokens(msc);
	reset_lex_index(msc->lex);
}

void	rejoin_tokens(t_msc *msc)
{
	t_list	*tmp;
	t_list	*tf;
	char	*buff;

	tmp = msc->lex;
	while (tmp && tmp->str && tmp->next)
	{
		tf = tmp->next;
		if (((tmp->str[0] == '>' && tf->str[0] == '>') || (tmp->str[0] == '<'
					&& tf->str[0] == '<')) && !tmp->str[1] && tmp->exp == 0)
		{
			buff = tmp->str;
			tmp->str = ft_strjoin(tmp->str, tmp->next->str);
			if (!tmp->str)
				malloc_error_free_exit(msc, buff, NULL);
			reset_order(tmp);
			free_two(tf->str, buff);
			free(tf);
		}
		tmp = tmp->next;
	}
}

void	reset_order(t_list *tmp)
{
	if (tmp->next->next)
	{
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
	}
	else
		tmp->next = NULL;
}

void	tokenize_individual_op(t_msc *msc, t_list *tmp, char op)
{
	char	*buff;
	int		i;

	i = 0;
	while (tmp->str[i] && tmp->str[i] != op
		&& (tmp->str[i] != '\'' && tmp->str[i] != '\"'))
		i++;
	i = jump_quotes(tmp->str, i);
	while (tmp->str[i] && tmp->str[i] != op)
		i++;
	if (tmp->str[i] == op)
	{
		if (tmp->str[i + 1] && i == 0)
			i = 1;
		else if (i == 0)
			return ;
		buff = tmp->str;
		if (!ft_lst_insert(tmp, ft_substr(buff, i, ft_strlen(buff) - i), msc))
			malloc_error_free_exit(msc, NULL, NULL);
		tmp->str = ft_substr(buff, 0, i);
		if (!tmp->str)
			malloc_error_free_exit(msc, NULL, NULL);
		free(buff);
	}
}

int	ft_lst_insert(t_list *node, char *s, t_msc *msc)
{
	t_list	*new_node;
	t_list	*next_node;

	if (!s)
		return (0);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		malloc_error_free_exit(msc, NULL, NULL);
	if (s)
		new_node->str = s;
	new_node->next = NULL;
	new_node->prev = node;
	new_node->msc = msc;
	new_node->quote_status = node->quote_status;
	new_node->exp = node->exp;
	next_node = node->next;
	if (next_node)
	{
		new_node->next = next_node;
		next_node->prev = new_node;
	}
	node->next = new_node;
	return (1);
}
