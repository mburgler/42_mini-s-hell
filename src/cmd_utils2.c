/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:47:20 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/13 00:33:38 by abektimi         ###   ########.fr       */
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
// char	**get_full_cmd(t_list *lst)
// {
// 	int				i;
// 	static int		p_count;
// 	static t_list	*tmp;

// 	if (!lst)
// 		return (NULL);
// 	i = 0;
// 	if (p_count == 0)
// 	{
// 		tmp = lst;
// 		p_count == 1;
// 	}
// 	while (tmp)
// 	{
// 		if (tmp->token_status != IS_PIPE)
// 			i++;
// 		else
// 		{
// 			tmp = tmp->next;
// 			break;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (tmp == NULL)
// 		p_count = 0;
// 	return (set_full_cmd(lst, i));
// }

// char	**get_full_cmd(t_list *lst)
// {
// 	int				wc;
// 	static t_list	*tmp;

// 	if (!lst)
// 		return (NULL);
// 	wc = 0;
// 	if (tmp == NULL)
// 		tmp = lst;
// 	while (tmp && (tmp->token_status != IS_PIPE))
// 		wc++;
	
// }

// //assembles the full_cmd variable
// //of each t_cmd node from t_list *lex
// char	**set_full_cmd(t_list *lst, int words)
// {
// 	int		i;
// 	char	**ret;

// 	i = 0;
// 	ret = malloc(sizeof(char *) * (words + 1));
// 	if (!ret)
// 		return (NULL);
	
// 	return (ret);
// }