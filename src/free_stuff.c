/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:54:00 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/20 17:50:34 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_null(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_arr(char **strs)
{
	int	i;

	if(!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free_null((void **)&strs);
}

void	free_all(t_msc *msc)
{
	t_list *tmp;

	while (msc->list)
	{
		tmp = msc->list;
		msc->list = msc->list->next;
		free_null((void **)&tmp->str);
		free_null((void **)&tmp);
	}
	ft_free_arr(msc->env_cpy);
	free_null((void **)&msc);
}
