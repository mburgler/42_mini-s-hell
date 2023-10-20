/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:22:50 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/19 20:38:19 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//deletes the 2D array created by lex_split()
void	free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
}

//splits the input received by readline() into separate parts,
//and creates a linked list with a node for each individual section
void	input_lexer(t_msc *msc)
{
	char	**tmp;

	if (quote_checker(msc->input) > 0)
		return ;
	tmp = lex_split(msc->input);
	msc->lex = init_lst(msc, tmp);
	free_2d_arr(tmp);
	if (!msc->lex)
		exit(1);
	//delete all and print appropriate error message in if-clause below
	if (search_estr(msc->lex) || search_opipe(msc->lex))
	{
		//ft_lstclear(&(msc->lex));
		printf("\nOPEN PIPE/EMPTY STRING FOUND\n");
	}
	printf("\n\n### TESTING THE LINKED LIST LEXER THING: ###\n\n");
	printf("~~ !! _ symbol added for better readability, not part of the string !! ~~\n\n");
	exp_head(msc); //MATTEO ADDED THIS
	tokenize_op(msc); //MATTEO ADDED THIS
	set_token_flag(msc->lex);
	//delete all and print appropriate error message in if-clause below
	if (consec_ops(msc->lex))
	{
		//ft_lstclear(&(msc->lex));
		printf("\nCANNOT HAVE CONSECUTIVE OPERATORS!\n");
	}
	ft_printlist(msc->lex);
	msc->cmd = init_cmd(msc, nb_of_cmds(msc->lex));
	// printf("\n\nNumber of cmds: %d\n\n", n_o_c(msc->cmd));
	// print2d(msc->cmd);
}

//ONLY INCLUDED FOR TESTING PURPOSES
void	ft_printlist(t_list *lst)
{
	t_list	*tmp;

	if (lst)
	{
		tmp = lst;
		while (tmp)
		{
			printf("Node %d contains: _%s_\n", tmp->id, tmp->str);
			printf("Quotes: %d\n", tmp->quote_status);
			printf("Token status: %d\n", tmp->token_status);
			tmp = tmp->next;
		}
	}
}