/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:25:49 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/21 14:51:41 by mburgler         ###   ########.fr       */
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
			if (ft_strlen(lst->str) == 0)
				return (1);
			lst = lst->next;
		}
	}
	return (0);
}

// //looks for an open pipe in the user input
// int search_opipe(t_list *lst)
// {
// 	int i;
//
// 	if (!lst)
// 		return (0);
// 	i = 0;
// 	while (lst->str[i] != '\0' && isws(lst->str[i]))
// 		i++;
// 	if (lst->str[i] == '|')
// 		return (1);
// 	while (lst->next)
// 		lst = lst->next;
// 	i = ft_strlen(lst->str);
// 	while (--i >= 0)
// 	{
// 		if (!isws(lst->str[i]))
// 		{
// 			if (lst->str[i] == '|')
// 				return (1);
// 			else
// 				return (0);
// 		}
// 	}
// 	return (0);
// }

//checks if a list node contains an operator from the list specified in the subject
void	set_token_flag(t_list *lst)
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		if (lst->str)
			lst->token_status = is_operator(lst->str);
		lst = lst->next;
	}
}

//returns a value between 301 and 305 using the preprocessor macros
//from minishell.h for easier reference throughout the runtime
int	is_operator(const char *s)
{
	if (ft_strncmp(s, "|", 1) == 0)
		return (IS_PIPE);
	else if (ft_strncmp(s, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (IP_REDIR);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (OP_REDIR);
	return (0);
}
