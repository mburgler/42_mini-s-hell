/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:13:35 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/04 14:42:44 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_head(t_msc *msc, t_cmd *cmd)
{
	if (!cmd->full_cmd[1])
	{
		ft_printf("Honestly, we don't care.\n\n");
		ft_printf("Lots of love,\nAlex and Matteo\n");
		g_sig_status = 0;
		return ;
	}
	if (!ft_strchr(cmd->full_cmd[1], '='))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n",
			cmd->full_cmd[1]);
		g_sig_status = 0;
		return ;
	}
	if (ft_strchr(cmd->full_cmd[1], '='))
	{
		export_new(msc, cmd);
		g_sig_status = 0;
		return ;
	}
}

void	export_new(t_msc *msc, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = ft_dup_envnew(cmd->full_cmd[1], msc);
	if (!msc->dup_env)
	{
		msc->dup_env = tmp;
		g_sig_status = 0;
		return ;
	}
	else
	{
		ft_envadd_back(&msc->dup_env, tmp);
		g_sig_status = 0;
		return ;
	}
}

//valid input regarding characters
// += 
// double occurence