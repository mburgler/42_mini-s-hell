/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:54:00 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/22 21:44:35 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	free_null(void **ptr)
// {
// 	if (ptr != NULL && *ptr != NULL)
// 	{
// 		free(*ptr);
// 		*ptr = NULL;
// 	}
// }

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
	if (msc->env_cpy)
		ft_free_arr(msc->env_cpy);
	// free_null((void **)&msc->env_cwd);
	if (msc->env_cwd)
		free(msc->env_cwd);
	//don't free msc->env_home, it's a pointer to an environment variable
	//free_null((void **)&msc->prompt_cwd);
	//free_null((void **)&msc->prompt);
	// free_null((void **)&msc);
	free(msc);
}
