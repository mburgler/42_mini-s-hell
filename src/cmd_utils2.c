/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:47:20 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/22 20:49:43 by abektimi         ###   ########.fr       */
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
			break ;
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

	if (no_pipes(lst))
		end++;
	printf("\n\nSTART = %d, END = %d\n\n", start, end);
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
	return (shorten_arr(ret, i));
}

char	**shorten_arr(char **ret, int len)
{
	int		i;
	int		j;
	char	**new;

	j = nb_of_estr(ret);
	if (j == 0)
		return (ret);
	new = malloc(sizeof(char *) * (len - j + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (ret[++i])
	{
		if (ft_strlen(ret[i]) > 0)
		{
			new[j] = ft_strdup(ret[i]);
			if (!new[j])
				return (del_split(new, j));
			j++;
		}
	}
	new[j] = NULL;
	free_2d_arr(ret);
	return (new);
}

int	nb_of_estr(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (ft_strlen(arr[i]) == 0)
			j++;
		i++;
	}
	return (j);
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
		while (cmds->full_cmd && cmds->full_cmd[i] != NULL)
		{
			printf("\n%s\n", cmds->full_cmd[i]);
			i++;
		}
		cmds = cmds->next;
	}
}
