/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:02:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 20:35:17 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	quit_child(int sig)
{
	char	core_dumper[10];
	int		i;

	(void)sig;
	i = -1;
	g_sig_status = 131;
	while (++i < 11)
		core_dumper[i] = 'q';
	(void)core_dumper;
}

//needed to shorten executor()
void	perror_and_or_set_eacces(void)
{
	perror("Error in executor()");
	strerror(errno);
	if (errno == EACCES)
		g_sig_status = 126;
}
