/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:22:50 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/28 02:12:59 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//deletes the 2D array created by lex_split()
void    del_tmp(char **tmp)
{
	int i;

	i = -1;
	if (tmp)
	{
		while (tmp[++i])
		{
			free(tmp[i]);
			tmp[i] = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

//splits the input received by readline() into separate parts,
//and creates a linked list with a node for each individual section
void    input_lexer(t_msc *msc)
{
	char    **tmp;

	if (quote_checker(msc->input) > 0)
		return ;
	tmp = lex_split(msc->input);
	msc->lex = init_lst(msc, tmp);
	printf("\n\n### TESTING THE LINKED LIST LEXER THING: ###\n\n");
	printf("~~ !! _ symbol added for better readability, not part of the string !! ~~\n\n");
	exp_head(msc); //MATTEO ADDED THIS
	//tokenize_op(msc);
	ft_printlist(msc->lex);
	del_tmp(tmp);
}

//ONLY INCLUDED FOR TESTING PURPOSES
void    ft_printlist(t_list *lst)
{
	t_list  *tmp;
	int     i;

	i = 0;
	if (lst)
	{
		tmp = lst;
		while (tmp)
		{
			printf("Node %d contains: _%s_\n", i, tmp->str);
			printf("Quotes: %d\n", tmp->quote_status);
			tmp = tmp->next;
			i++;
		}
	}
}