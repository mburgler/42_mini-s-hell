/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:25:49 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/01 18:59:59 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//looks for empty string in the user input
int search_estr(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst)
		{
			if (lst->str[0] == '\0')
				return (1);
			lst = lst->next;
		}
		return (0);
	}
	return (0);
}

//looks for an open pipe in the user input
int search_opipe(t_list *lst)
{
	int i;
	
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	i = ft_strlen(lst->str);
	while (--i >= 0)
	{
		if (!isws(lst->str[i]))
		{
			if (lst->str[i] == '|')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}
