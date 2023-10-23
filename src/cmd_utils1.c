/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:25:32 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/23 15:33:31 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//creates and returns a blank node of type t_cmd
t_cmd	*ft_cmdnew(t_msc *ms, int i)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->cmd = NULL;
	ret->option = NULL;
	ret->full_cmd = cmd_setter(ms->lex);
	ret->index = i;
	ret->fd_in = 0;
	ret->fd_out = 1;
	ret->fd_in_type = 0;
	ret->fd_out_type = 0;
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
		if ((*lst)->cmd)
			free((*lst)->cmd);
		if ((*lst)->option)
			free((*lst)->option);
		if ((*lst)->full_cmd)
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

	reset_lex_index(msc->lex);
	i = 1;
	ret = ft_cmdnew(msc, 0);
	if (!ret)
		return (NULL);
	set_in_out_file(ret);
	while (i < nb)
	{
		tmp = ft_cmdnew(msc, i);
		ft_cmdadd_back(&ret, tmp);
		if (!tmp)
		{
			ft_cmdclear(&ret);
			free(ret);
			return (NULL);
		}
		set_in_out_file(tmp); // Matteo added this
		i++;
	}
	return (ret);
}
