/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:06:38 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/28 20:19:05 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	no_valid_path(t_msc *msc)
{
	t_env	*tmp;

	if (!msc || !msc->dup_env)
		return (1);
	tmp = msc->dup_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	is_empty_arg(const char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 34)
		{
			if (input[i + 1] == 34)
				return (erroneous_input());
		}
		else if (input[i] == 39)
		{
			if (input[i + 1] == 39)
				return (erroneous_input());
		}
		i++;
	}
	return (0);
}

int	erroneous_input(void)
{
	errno = 1;
	perror("<3 Input error <3");
	strerror(errno);
	g_sig_status = 1;
	return (1);
}

void	kill_in_out_file_sub(t_cmd *cmd)
{
	if (cmd->full_cmd == NULL)
		free_msc_and_exit(cmd->msc, "Memory allocation error: malloc\n");
}
