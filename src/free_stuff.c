/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:54:00 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/10 16:45:00 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_arr(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	// free_null((void **)&strs);
	free(strs);
}

void	free_structs_and_input(t_msc *msc)
{
	if (!msc)
		return ;
	if (msc->input)
		free(msc->input);
	if (msc->lex)
		ft_lstclear(&(msc->lex));
	if (msc->cmd)
		ft_cmdclear(&(msc->cmd));
}

void	free_all(t_msc *msc)
{
	if (!msc)
		return ;
	if (msc->lex)
		ft_lstclear(&(msc->lex));
	if (msc->cmd)
		ft_cmdclear(&(msc->cmd));
	if (msc->input)
		free(msc->input);
	if (msc->dup_env)
		ft_envclear(&msc->dup_env);
	free(msc);
}
