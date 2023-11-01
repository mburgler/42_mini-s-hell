/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:00:02 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/01 02:20:14 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	malloc_error_free_exit(t_msc *msc, char *to_free, char *to_free2)
{
	if (to_free)
		free(to_free);
	if (to_free2)
		free(to_free2);
	perror("Memory allocation error: malloc\n");
	if (msc)
		free_all(msc);
	exit(1);
}

void	free_msc_and_exit(t_msc *msc, char *msg)
{
	perror(msg);
	if (msc)
		free_all(msc);
	exit(1);
}

void	free_msc_and_errno(t_msc *msc, char *msg)
{
	char	*err_msg;
	char	*full_msg;

	err_msg = ft_strjoin(strerror(errno), "\n");
	full_msg = ft_strjoin(msg, err_msg);
	perror(full_msg);
	free(err_msg);
	free(full_msg);
	if (msc)
		free_all(msc);
	exit(1);
}
