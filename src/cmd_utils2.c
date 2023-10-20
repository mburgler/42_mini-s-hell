/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:47:20 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/19 20:44:50 by abektimi         ###   ########.fr       */
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

char	**cmd_setter(t_list *lst)
{
	static int		start;
	static int		end;
	static t_list	*tmp;

	if (!lst)
		return (NULL);
	if (tmp == NULL)
	{
		tmp = lst;
		start = 0;
		end = 0;
	}
	while (tmp)
	{
		start = end;
		if (tmp->token_status == IS_PIPE || tmp->next == NULL)
		{
			end = tmp->id;
			tmp = tmp->next;
			break;
		}
		tmp = tmp->next;
	}
	return (get_full_cmd(lst, start, end));
}

//creates a 2D array containing the strings of the lexer list
//separated by pipes and/or the end of the list
char	**get_full_cmd(t_list *lst, int start, int end)
{
	int		i;
	char	**ret;

	ret = malloc(sizeof(char *) * (end - start + 1));
	if (!ret)
		return (NULL);
	while (lst->id != start)
		lst = lst->next;
	if (lst->token_status == IS_PIPE)
		lst = lst->next;
	i = 0;
	while (lst != NULL && lst->token_status != IS_PIPE)
	{
		ret[i] = ft_strdup(lst->str);
		if (ret[i] == NULL)
			return (del_split(ret, i));
		i++;
		lst = lst->next;
	}
	ret[i] = NULL;
	return (ret);
}

//ONLY MEANT FOR TESTING PURPOSES
void	print2d(t_cmd *cmds)
{
	int	i;
	int	j;

	if (!cmds)
	{
		printf("\n\nCouldn't print stuff\n\n");
		return ;
	}
	j = 0;
	while (cmds)
	{
		i = 0;
		printf("\nNode %d:\n\n", j++);
		while (cmds->full_cmd[i] != NULL)
		{
			printf("\n%s\n", cmds->full_cmd[i]);
			i++;
		}
		cmds = cmds->next;
	}
}