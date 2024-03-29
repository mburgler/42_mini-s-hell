/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:00:02 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/23 19:46:48 by abektimi         ###   ########.fr       */
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
	perror(msg);
	strerror(errno);
	if (msc)
		free_all(msc);
	exit(1);
}

void	exit_child_and_errno(char *msg)
{
	perror(msg);
	strerror(errno);
	exit(1);
}

void	exit_child_eacces(t_cmd *cmd, char *path, char **c_cmd, char **c_env)
{
	free_exec_temps(path, NULL, c_cmd, c_env);
	free_all(cmd->msc);
	perror("Error in executor()");
	strerror(EACCES);
	g_sig_status = 126;
	exit(g_sig_status);
}
