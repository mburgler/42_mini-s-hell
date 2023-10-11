/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:47:20 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/11 15:59:37 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//counts and returns the number of sections
//in t_list *lex which are separated by pipes
int nb_of_cmds(t_list *lst)
{
	int	ret;

	ret = 1;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->token_status == IS_PIPE)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

//separates the t_list *lex into parts which
//set_full_cmd() can use
char	**get_full_cmd(t_list *lst)
{
	int				i;
	static int		cmds_done;
	static t_list	*tmp;

	if (!lst)
		return (NULL);
	i = 0;
	if (cmds_done == 0)
	{
		tmp = lst;
		cmds_done = 1;
	}
	while (tmp)
	{
		if (tmp->token_status != IS_PIPE)
			i++;
		else
		{
			tmp = tmp->next;
			break;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		cmds_done = 0;	
	(void)i; //FOR COMPILING PLS FIX
	return (NULL);// set_full_cmd(lst, i));
}

//assembles the full_cmd variable
//of each t_cmd node from t_list *lex
char	**set_full_cmd(t_list *lst, int words)
{
	(void)lst;
	(void)words;
	return(NULL);
}