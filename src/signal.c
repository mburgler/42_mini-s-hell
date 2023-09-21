/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:02:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/21 17:17:23 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "../inc/minishell.h"

void handle_sigint(int sig) 
{
    (void)sig;
	g_sig_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//rl_replace_line("", 0);
	rl_on_new_line();
}
