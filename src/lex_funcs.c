/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:22:50 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/02 01:54:45 by abektimi         ###   ########.fr       */
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

//checks for syntax errors after the input was lexed and expanded
int	check_syntax(t_msc *msc)
{
	if (consec_ops(msc))
	{
		printf("syntax error: consecutive operators\n");
		return (0);
	}
	if (check_open_op(msc))
	{
		printf("syntax error: open operator\n");
		return (0);
	}
	if (pipe_first(msc))
	{
		printf("syntax error: pipe at the beginning of the command\n");
		return (0);
	}
	return (1);
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
		free_msc_and_exit(msc, "Memory allocation error: malloc\n");
	exp_head(msc);
	tokenize_op(msc);
	set_token_flag(msc->lex);
	kill_quotes(msc);
	if (check_syntax(msc) == 0)
		return ;
	ft_printlist(msc->lex);
	msc->cmd = init_cmd(msc, nb_of_cmds(msc->lex));
	set_cmd_and_option(msc->cmd);
	printcmds(msc->cmd);
	//make_pipeline(msc);
}

//ONLY INCLUDED FOR TESTING PURPOSES
void	ft_printlist(t_list *lst)
{
	t_list	*tmp;

	if (lst)
	{
		tmp = lst;
		printf("\n\n### TESTING THE LINKED LIST LEXER ###\n\n");
		while (tmp)
		{
			printf("Node %d contains: _%s_\n", tmp->id, tmp->str);
			printf("Quotes: %d\n", tmp->quote_status);
			printf("Token status: %d\n", tmp->token_status);
			tmp = tmp->next;
		}
	}
}
