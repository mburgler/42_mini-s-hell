/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:12:13 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 20:15:32 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//frees all nodes of a cmd list 'lst'
void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!lst || !(*lst))
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->cmd)
			free((*lst)->cmd);
		if ((*lst)->option)
			free((*lst)->option);
		if ((*lst)->full_cmd)
			free_2d_arr(&((*lst)->full_cmd));
		if ((*lst)->fd_out > 1)
			close((*lst)->fd_out);
		if ((*lst)->fd_in > 0)
		{
			close((*lst)->fd_in);
			if ((*lst)->fd_in_type == HEREDOC)
				kill_heredoc(lst);
		}
		free(*lst);
		*lst = tmp;
	}
}

void	kill_heredoc(t_cmd **lst)
{
	unlink((*lst)->heredoc_name);
	free((*lst)->heredoc_name);
}

int	no_pipes(t_list *lst)
{
	if (!lst)
		return (1);
	while (lst)
	{
		if (lst->token_status == IS_PIPE)
			return (0);
		lst = lst->next;
	}
	return (1);
}

//ONLY MEANT FOR TESTING PURPOSES
// void	printcmds(t_cmd *cmds)
// {
// 	int	i;

// 	if (!cmds)
// 	{
// 		printf("\n\nCouldn't print stuff\n\n");
// 		return ;
// 	}
// 	while (cmds)
// 	{
// 		i = 0;
// 		printf("\nNode %d:\n\n", cmds->index);
// 		while (cmds->full_cmd && cmds->full_cmd[i] != NULL)
// 		{
// 			printf("\n%s\n", cmds->full_cmd[i]);
// 			i++;
// 		}
// 		printf("cmd: %s\n", cmds->cmd);
// 		//printf("option: %s\n", cmds->option);
// 		//ft_print2d(cmds->option);
// 		printf("pid: %d\n", cmds->pid);
// 		printf("fd_in: %d\n", cmds->fd_in);
// 		printf("fd_in_type: %d\n", cmds->fd_in_type);
// 		printf("fd_out: %d\n", cmds->fd_out);
// 		printf("fd_out_type: %d\n", cmds->fd_out_type);
// 		printf("--------------------\n");
// 		cmds = cmds->next;
// 	}
// }
