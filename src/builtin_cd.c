/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:07:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/06 13:34:44 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_cd_head(t_cmd *cmd)
{
	char	*go_to;
	char	*to_free;

	go_to = set_path(cmd);
	printf("### DEBUG go_to: %s ###\n", go_to);
	if (!go_to || chdir(go_to) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", go_to, strerror(errno));
		g_sig_status = 1;
		free(go_to);
		return ;
	}
	if (ft_getenv("PWD", cmd->msc))
	{
		to_free = ft_strjoin("OLDPWD=", ft_getenv("PWD", cmd->msc));
		export_core(cmd->msc, to_free);
		to_free = ft_strjoin_free("PWD=", go_to, to_free, NULL);
		export_core(cmd->msc, to_free);
		free(to_free);
	}
	else
		unset_core(cmd->msc, "OLDPWD");
	g_sig_status = 0;
	free(go_to);
}

char	*set_path(t_cmd *cmd)
{
	char	*go_to;

	if (!cmd->full_cmd[1] || (cmd->full_cmd[1][0] == '~'
		&& !cmd->full_cmd[1][1]))
		go_to = ft_strdup(ft_getenv("HOME", cmd->msc));
	else if (cmd->full_cmd[1][0] == '-')
		go_to = ft_strdup(ft_getenv("OLDPWD", cmd->msc));
	else if (cmd->full_cmd[1][0] == '/')
		go_to = ft_strdup(cmd->full_cmd[1]);
	else
	{
		go_to = getcwd(NULL, 0);
		go_to = ft_strjoin_free(go_to, "/", go_to, NULL);
		go_to = ft_strjoin_free(go_to, cmd->full_cmd[1], go_to, NULL);
	}
	return (go_to);
}

//./inc
// issue of //Users
//go_to == NULL || cmd->full_cmd[1][0] == '~' || 

//pwd becomes old pwd; uses var pwd
//if pwd is unset, then old pwd becomes unset after one turn of cd
//get_cwd is used everywhere else
// cd - goes back to OLDPWD
//malloc protetion

//if home unset
//bash: cd: HOME not set

/* COPILOT

	else if(cmd->full_cmd[1] == '-')
		go_to = ft_strdup(ft_getenv("OLDPWD", cmd->msc));
	else if (cmd->full_cmd[1][0] == '~')
	{
		go_to = ft_strdup(ft_getenv("HOME", cmd->msc));
		go_to = ft_strjoin_free(go_to, "/", go_to, NULL);
		go_to = ft_strjoin_free(go_to, cmd->full_cmd[1] + 1, go_to, NULL);
	}
	else if (cmd->full_cmd[1][0] == '/')
		go_to = ft_strdup(cmd->full_cmd[1]);
	else if (cmd->full_cmd[1][0] == '.')
	{
		go_to = getcwd(NULL, 0);
		go_to = ft_strjoin_free(go_to, "/", go_to, NULL);
		go_to = ft_strjoin_free(go_to, cmd->full_cmd[1], go_to, NULL);
	}
	else
	{
		go_to = getcwd(NULL, 0);
		go_to = ft_strjoin_free(go_to, "/", go_to, NULL);
		go_to = ft_strjoin_free(go_to, cmd->full_cmd[1], go_to, NULL);
	}

*/
