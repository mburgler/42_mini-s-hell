/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:25:32 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/10 17:50:57 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//creates and returns a blank node of type t_cmd
t_cmd	*ft_cmdnew(t_msc *ms)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->cmd = NULL;
	ret->option = NULL;
	ret->full_cmd = NULL;
	ret->fd_in = 0;
	ret->fd_out = 1;
	ret->next = NULL;
	ret->prev = NULL;
	ret->msc = ms;
	return (ret);
}

//adds a node 'new' to the back of cmd list 'lst'
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst && new)
	{
		if (*lst)
		{
			tmp = ft_cmdlast(*lst);
			tmp->next = new;
			new->prev = tmp;
		}
		else
		{
			*lst = malloc(sizeof(t_cmd));
			*lst = new;
		}
	}
}

//returns a pointer to the last node of cmd list 'lst'
t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (lst != NULL)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

//frees all nodes of a cmd list 'lst'
void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!lst || !(*lst))
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->cmd);
		free((*lst)->option);
		free_2d_arr((*lst)->full_cmd);
		free(*lst);
		*lst = tmp;
	}
}

//creates and initializes a cmd list with the required number of nodes
//returns a pointer to the first node in the cmd list
t_cmd	*init_cmd(t_msc	*msc, int nb)
{
	t_cmd	*ret;
	t_cmd	*tmp;
	int		i;

	i = 0;
	ret = ft_cmdnew(msc);
	if(!ret)
		return (NULL);
	while (i < nb)
	{
		tmp = ft_cmdnew(msc);
		ft_cmdadd_back(&ret, tmp);
		if (!tmp)
		{
			ft_cmdclear(&ret);
			free(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}