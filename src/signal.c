/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:02:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/28 15:56:36 by mburgler         ###   ########.fr       */
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

void	handle_sigint_parent(int sig)
{
	(void)sig;
	g_sig_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
