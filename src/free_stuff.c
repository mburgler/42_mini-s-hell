/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:54:00 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 22:26:47 by abektimi         ###   ########.fr       */
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
	{
		ft_lstclear(&(msc->lex));
		msc->lex = NULL;
	}
	if (msc->cmd)
	{
		close_all(msc->cmd);
		ft_cmdclear(&(msc->cmd));
		msc->cmd = NULL;
	}
	if (msc->input)
	{
		free(msc->input);
		msc->input = NULL;
	}
	if (msc->dup_env)
	{
		ft_envclear(&msc->dup_env);
		msc->dup_env = NULL;
	}
	free(msc);
	msc = NULL;
}

void	free_msc_and_exit_success(t_msc *msc)
{
	if (msc)
		free_all(msc);
	exit(0);
}

void	main_free(t_msc *msc)
{
	if (msc->stop_file_error != 0)
	{
		free(msc->input);
		if (msc->str_file_error)
		{
			if (msc->stop_file_error == 1)
			{
				write(2, "permission denied/non existing: ", 32);
				write(2, msc->str_file_error, ft_strlen(msc->str_file_error));
				write(2, "\n", 1);
			}
			free(msc->str_file_error);
			msc->str_file_error = NULL;
		}
	}
	else
		free_structs_and_input(msc);
	msc->stop_file_error = 0;
}
