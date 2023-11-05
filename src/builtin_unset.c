/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:13:39 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/06 00:07:02 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_unset_head(t_msc *msc, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->full_cmd[i])
	{
		unset_core(msc, cmd->full_cmd[i]);
		i++;
	}
	g_sig_status = 0;
}

void	unset_core(t_msc *msc, char *str)
{
	t_env	*tmp;

	tmp = msc->dup_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			unset_indiv_node(msc, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	unset_indiv_node(t_msc *msc, t_env *node)
{
	t_env	*tmp;

	tmp = msc->dup_env;
	if (tmp == node)
	{
		msc->dup_env = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free(node->key);

	free(node->value);
	free(node);
}
