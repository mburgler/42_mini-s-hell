/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:11:06 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/23 20:32:40 by abektimi         ###   ########.fr       */
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

//OPEN
// - handle $?
// - handle heredoc
// - local env copy for when doing cd or (un)setting vars
//errorhandling when two fd
// - $mburgler for minishell $ $$"$USER"
// - DONE echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" results in syntax error: consecutive operators
// 	- resplit for l$s -la
// - fix $cmds.txt

//DONE
// - $mburgler for minishell $ $$"$USER"
//- kill op and adjacent file
//	- DONE $"$" doesnt show anything

int	set_in_out_file(t_cmd *cmd)
{
	int i;
	t_list	*tmp;

	i = 0;
	tmp = shift_lex_for_cmd(cmd, cmd->msc->lex);
	while (cmd->full_cmd[i])
	{
		if(tmp->quote_status == 0)
		{
			if(cmd->full_cmd[i][0] == '>' && !cmd->full_cmd[i][1])
				ft_outfile(cmd, i + 1, OP_REDIR);
			else if(cmd->full_cmd[i][0] == '>' && cmd->full_cmd[i][1] == '>')
				ft_outfile(cmd, i + 1, APPEND);
			else if(cmd->full_cmd[i][0] == '<' && !cmd->full_cmd[i][1])
				ft_infile(cmd, i + 1, OP_REDIR);
			else if(cmd->full_cmd[i][0] == '<' && cmd->full_cmd[i][1] == '<')
				ft_infile(cmd, i + 1, HEREDOC);
		}
		tmp = tmp->next;
		i++;
	}
	kill_in_out_file(cmd);
	return (0);
}

void	ft_outfile(t_cmd *cmd, int i, int type)
{
	if (cmd->fd_out > 1)
		close(cmd->fd_out);
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
	if (cmd->fd_out == -1)
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

//echo test >kkkk"helpmeneu"

void	kill_in_out_file(t_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = shift_lex_for_cmd(cmd, cmd->msc->lex);
	while (cmd->full_cmd[i])
	{
		if ((cmd->full_cmd[i][0] == '>' || cmd->full_cmd[i][0] == '<')
			&& tmp->quote_status == 0)
		{
			free(cmd->full_cmd[i]);
			cmd->full_cmd[i] = NULL;
			cmd->full_cmd[i] = ft_strdup("");
			free(cmd->full_cmd[i + 1]);
			cmd->full_cmd[i + 1] = NULL;
			cmd->full_cmd[i + 1] = ft_strdup("");
		}
		i++;
		tmp = tmp->next;
	}
	cmd->full_cmd = shorten_arr(cmd->full_cmd, i);
	if (cmd->full_cmd == NULL)
		free_msc_and_exit(cmd->msc, "Memory allocation error: malloc\n");
}

t_list	*shift_lex_for_cmd(t_cmd *cmd, t_list *tmp)
{
	int i;

	i = 0;
	if (cmd->prev == NULL)
		return (tmp);
	else
	{
		while (cmd->index != i)
		{
			while (tmp->token_status != IS_PIPE)
			{
				tmp = tmp->next;
			}
			tmp = tmp->next;
			i++;
		}
	}
	return (tmp);
}
