/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:11:06 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 20:26:22 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
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
// PARTLY - handle $?
// - handle heredoc
// - local env copy for when doing cd or (un)setting vars
// - errorhandling when two fd
// - $mburgler for minishell $ $$"$USER"
// - resplit for l$s -la
// - fix $cmds.txt
// - ❯ echo hey$USER"$USER"'$USER'$USER
//		should be: heymburglermburgler$USERmburgler
//		is: _heymburglermburgler'mburgler'mburgler_

//DONE
// - $mburgler for minishell $ $$"$USER"
//- kill op and adjacent file
//	- DONE $"$" doesnt show anything
// - DONE echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"
//results in syntax error: consecutive operators

int	set_in_out_file(t_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = shift_lex_for_cmd(cmd, cmd->msc->lex);
	while (cmd->full_cmd[i])
	{
		if (tmp->quote_status == 0)
		{
			if (cmd->full_cmd[i][0] == '>' && !cmd->full_cmd[i][1])
				ft_outfile(cmd, i + 1, OP_REDIR);
			else if (cmd->full_cmd[i][0] == '>' && cmd->full_cmd[i][1] == '>')
				ft_outfile(cmd, i + 1, APPEND);
			else if (cmd->full_cmd[i][0] == '<' && !cmd->full_cmd[i][1])
				ft_infile(cmd, i + 1, IP_REDIR);
			else if (cmd->full_cmd[i][0] == '<' && cmd->full_cmd[i][1] == '<')
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
		if (cmd->msc->stop_file_error != 2)
			cmd->msc->stop_file_error = 1;
		if (cmd->msc->str_file_error)
			free(cmd->msc->str_file_error);
		cmd->msc->str_file_error = ft_strdup(cmd->full_cmd[i]);
	}
}

void	ft_infile(t_cmd *cmd, int i, int type)
{
	if (cmd->fd_in > 0)
	{
		close(cmd->fd_in);
		if (cmd->fd_in_type == HEREDOC)
		{
			unlink(cmd->heredoc_name);
			free(cmd->heredoc_name);
		}
	}
	if (type == IP_REDIR)
	{
		cmd->fd_in = open(cmd->full_cmd[i], O_RDWR);
		cmd->fd_in_type = IP_REDIR;
	}
	if (type == HEREDOC)
		cmd->fd_in = handle_heredoc(cmd, i);
	if (cmd->fd_in == -1)
	{
		g_sig_status = 1;
		if (cmd->msc->stop_file_error != 2)
			cmd->msc->stop_file_error = 1;
		if (cmd->msc->str_file_error)
			free(cmd->msc->str_file_error);
		cmd->msc->str_file_error = ft_strdup(cmd->full_cmd[i]);
	}
}

int	handle_heredoc(t_cmd *cmd, int i)
{
	char	*nmb_itoa;
	char	*buff;
	int		fd;

	nmb_itoa = ft_itoa(cmd->index);
	cmd->heredoc_name = ft_strjoin(".tmp_heredoc", nmb_itoa);
	fd = open(cmd->heredoc_name, O_CREAT | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free(nmb_itoa);
	cmd->fd_in_type = HEREDOC;
	if (fd == -1)
		return (fd);
	g_sig_status = 0;
	while (1)
	{
		buff = readline("minidoc> ");
		buff = bootstrap_exp_heredoc(buff, cmd->msc);
		if (heredoc_break_loop(buff, cmd, i) == 1)
			break ;
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
	return (fd);
}

int	heredoc_break_loop(char *buff, t_cmd *cmd, int i)
{
	if (g_sig_status == 130 && buff && cmd->msc)
	{
		free(buff);
		cmd->msc->stop_file_error = 2;
		if (cmd && cmd->msc && cmd->msc->str_file_error)
		{
			free(cmd->msc->str_file_error);
			cmd->msc->str_file_error = NULL;
		}
		return (1);
	}
	if (!ft_strncmp(cmd->full_cmd[i], buff, ft_strlen(cmd->full_cmd[i])))
	{
		free(buff);
		return (1);
	}
	return (0);
}
