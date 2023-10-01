/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:17:00 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/01 04:55:26 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*TO DO
1. Iterate over the two-dimensional array
2. Whenever a redirection is found, check the type of redirection and retrieve a file descriptor containing the info we need as the infile
3. Check that the file descriptor that has been opened is valid (!= -1) and continue
4. If a pipe is found, add a new node to the list of commands
5. In all other cases add whatever words are found to the argument list (``argv``) we call ``full_cmd``

cmds:
	cmd 1:
		infile: 0 (default)
		outfile: 1 (redirected to pipe)
		full_path: NULL (because echo is a builtin)
		full_cmd: {echo, hello there, how, are, you doing?, pixel, NULL}
	cmd 2:
		infile: 0 (contains output of previous command)
		outfile: 3 (fd corresponding to the open file 'outfile')
		full_path: /bin/wc
		full_cmd: {wc, -l, NULL}
envp: (envp from main)
pid: process ID of current instance
g_status: 0 (if last command exits normally)
*/

void	pars_head(t_msc *msc)
{
	(void)msc;
	//pars_init_cmd(msc);

}

int	pars_list(t_msc *msc)
{
	(void)msc;
	//finsih tmrw
	return(0);
}

void	pars_init_cmd(t_msc *msc)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		malloc_error_free_exit(msc, NULL, NULL);
	msc->cmd = cmd;
	cmd->full_cmd = ft_calloc(1, sizeof(char *));
	if (!cmd->full_cmd)
		malloc_error_free_exit(msc, NULL, NULL);
	cmd->next = NULL;
}