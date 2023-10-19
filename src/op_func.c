/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 00:31:09 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/18 17:04:52 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void tokenize_op(t_msc *msc)
{
    t_list    *tmp;

    tmp = msc->lex;
    while (tmp && tmp->str)
    {
        if(tmp->quote_status == 0)
        {
			check_for_syntax_error(msc, tmp);
            tokenize_individual_op(msc, tmp, '|');
            tokenize_individual_op(msc, tmp, '>');
            tokenize_individual_op(msc, tmp, '<');
        }
        tmp = tmp->next;
    }
}

void	check_for_syntax_error(t_msc *msc, t_list *tmp)
{
	int	i;
	
	i = 0;
	while (tmp && tmp->str)
	{
		while(tmp->str[i] != '|' && tmp->str[i] != '>' &&
			tmp->str[i] != '<' && tmp->str[i] != '\0')
			i++;
		if(cse2(tmp, i, '|') || cse2(tmp, i, '>') || cse2(tmp, i, '<'))
		{
			ft_printf_2("minishell: syntax error near unexpected token `%c'\n",
			tmp->str[i]);
			g_sig_status = 258;
			//malloc_error_free_exit(msc, NULL, NULL);
			(void)msc; //dont end
		}
		tmp = tmp->next;
	}
}

int	cse2(t_list *tmp, int i, char op)
{
	if(tmp->str[i] == op && i > 0)
	{
		if(tmp->str[i - 1] == op ||
			(tmp->next && tmp->next->quote_status == 0 && tmp->next->str[0] == op))
			return (1);
	}
	else if(tmp->str[i] == op && i == 0)
		if((tmp->str[i + 1] && tmp->str[i + 1] == op) ||
			(tmp->next && tmp->next->quote_status == 0 && tmp->next->str[0] == op))
			return (1);
	return (0);
	//handle case: test hallo | |abc 
	//error with test me |a |
	//### GIT PUSH ### correct branch??
	//current logic would not recognise second opperator double as error after single op check
}

void	tokenize_individual_op(t_msc *msc, t_list *tmp, char op)
{
	char	*buff;
	int		i;

	i = 0;
	while (tmp->str[i] && tmp->str[i] != op)
		i++;
	if(tmp->str[i] == op)
	{
		if(tmp->str[i + 1] && i == 0)
			i = 1;
		else if(i == 0)
			return ;
		buff = tmp->str;
		if(!ft_lst_insert(tmp, ft_substr(buff, i, ft_strlen(buff) - i), msc))
			malloc_error_free_exit(msc, NULL, NULL);
		tmp->str = ft_substr(buff, 0, i);
		if(!tmp->str)
			malloc_error_free_exit(msc, NULL, NULL);
		free(buff);
	}
}

int	ft_lst_insert(t_list *node, char *s, t_msc *msc)
{
	t_list	*new_node;
	t_list	*next_node;

	if(!s)
		return (0);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		malloc_error_free_exit(msc, NULL, NULL);
	if(s)
		new_node->str = s;
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
	return (1);
}

//ARCHIVE
//
//main body of tokenize_individual_op
//
// if(tmp->str[i] == op && i > 0)
// {
// 	buff = tmp->str;
// 	if(!ft_lst_insert(tmp, ft_substr(buff, i, ft_strlen(buff) - i), msc))
// 		malloc_error_free_exit(msc, NULL, NULL);
// 	tmp->str = ft_substr(buff, 0, i);
// 	if(!tmp->str)
// 		malloc_error_free_exit(msc, NULL, NULL);
// 	free(buff);
// }
// else if(tmp->str[i] == op && tmp->str[i + 1] && i == 0)
// {
// 	buff = tmp->str;
// 	if(!ft_lst_insert(tmp, ft_substr(buff, 1, ft_strlen(buff) - 1), msc))
// 		malloc_error_free_exit(msc, NULL, NULL);
// 	tmp->str = ft_substr(buff, 0, 1);
// 	if(!tmp->str)
// 		malloc_error_free_exit(msc, NULL, NULL);
// 	free(buff);
// }