/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:02:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/21 13:47:43 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_sigint(int sig) 
{
    (void)sig;  // To avoid unused parameter warning
    // write(1, "\n", 1);  // Write a new line
	//char *prmt = "dies ist der prompt $";
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//write(STDOUT_FILENO, prmt, ft_strlen(prmt));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig_status = 42;
    // Display a new prompt here
}