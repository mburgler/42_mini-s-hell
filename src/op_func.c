/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 00:31:09 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/28 02:06:28 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tokenize_op(t_msc *msc)
{
	t_list	*tmp;

	tmp = msc->lex;
	while (tmp && tmp->str)
	{
		if(tmp->quote_status == 0)
		{
			tokenize_individual_op(msc, tmp, '|');
			tokenize_individual_op(msc, tmp, '>');
			tokenize_individual_op(msc, tmp, '<');
		}
		tmp = tmp->next;
	}
}

/*THINGS TO CONSIDER
- first list element
- last list element
- multiple ops in a row
- ops with whitespace around them
- op as first
- op as last
- op as only
- op as first and last
*/

void	tokenize_individual_op(t_msc *msc, t_list *tmp, char op)
{
	char	*to_free;
	int		i;

	i = 0;
	while (tmp->str[i] && tmp->str[i] != op)
		i++;
	if(tmp->str[i] == op && i > 0)
	{
		to_free = tmp->str;
		tmp->str = ft_substr(tmp->str, 0, i);
		free(to_free);
		to_free = ft_substr(tmp->str, i, ft_strlen(tmp->str) - i);
		ft_lst_insert(tmp, "TEST", msc);
	}
}

void	ft_lst_insert(t_list *node, const char *s, t_msc *msc)
{
	t_list	*new_node;
	t_list	*next_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		malloc_error_free_exit(msc, NULL, NULL);
	if(s)
		new_node->str = ft_strdup(s);
	new_node->next = NULL;
	new_node->prev = node;
	new_node->msc = msc;
	new_node->quote_status = node->quote_status;
	next_node = node->next;
	if (next_node)
	{
		new_node->next = next_node;
		next_node->prev = new_node;
	}
	node->next = new_node;
}
