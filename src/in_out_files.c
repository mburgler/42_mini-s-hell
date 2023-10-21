/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:11:06 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/21 19:42:24 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
1. Iterate over the two-dimensional array
2. Whenever a redirection is found, check the type of redirection and retrieve a file descriptor containing the info we need as the infile
3. Check that the file descriptor that has been opened is valid (!= -1) and continue
4. If a pipe is found, add a new node to the list of commands
5. In all other cases add whatever words are found to the argument list (``argv``) we call ``full_cmd``

echo "Hallo" > datei.txt
> datei.txt echo "Hallo"
echo > datei.txt "Hallo"
sort < datei.txt
cat < eingabe.txt > ausgabe.txt
no whitespaces between < <
<DATEINAME ist dasselbe wie < DATEINAME
*/

// expand . and .. in pathnames
// expand ~ to home directory
//-> can execv handle relative paths on its own?

//>: Redirects standard output to a file, overwriting the file.
//>>: Redirects standard output to a file, appending to the file.
//<: Redirects standard input from a file.
//<<: Here document

//TO DO MATTEO
// - handle $?
// - handle heredoc

// void	handle_op(t_msc *msc, t_cmd cmd, )
// {
	
// }
// {

// }

// int	open_outfile
// {
	
// }

int	set_in_out_file(t_cmd *cmd)
{
	int i;

	i = 0;
	printf("###debug0###\n");
	while (cmd->full_cmd[i])
	{
		printf("###debug1###\n");
		if(cmd->full_cmd[i][0] == '>' && !cmd->full_cmd[i][1])
			ft_outfile(cmd, i + 1, OP_REDIR);
		else if(cmd->full_cmd[i][0] == '>' && cmd->full_cmd[i][1] == '>')
			ft_outfile(cmd, i + 1, APPEND);
		else if(cmd->full_cmd[i][0] == '<' && cmd->full_cmd[i][1] == '<')
			ft_infile(cmd, i + 1, HEREDOC);
		i++;
		printf("###debug2###\n");
	}
	//errorhandling when two fd
	//kill op and adjacent file
	return (0);
}

void	ft_outfile(t_cmd *cmd, int i, int type)
{
	if (type == OP_REDIR)
	{
		cmd->fd_out = open(cmd->full_cmd[i], O_CREAT | O_RDWR | O_TRUNC, 
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		cmd->fd_out_type = OP_REDIR;
	}
	else if (type == APPEND)
	{
		cmd->fd_out = open(cmd->full_cmd[i], O_CREAT | O_WRONLY | O_APPEND, 
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		cmd->fd_out_type = APPEND;
	}
	printf("####fd: %d\n", cmd->fd_out);
	if(cmd->fd_out == -1)
	{
		g_sig_status = 1;
		printf("ERROR w/ output redirection\n");
	}
}

void	ft_infile(t_cmd *cmd, int i, int type)
{
	(void)cmd;
	(void)i;
	(void)type;
}
