/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:02:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/14 17:13:24 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//rl_replace_line("", 0);
	rl_on_new_line();
}
