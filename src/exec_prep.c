/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:48:41 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/11 22:36:48 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//sets the cmd and option variables in each node of the list of type t_cmd
/*
NOTE TO SELF on ft_strdup: no need to remove whitespaces, because commands
such as wc, ls, and so on will reject flags if the respective string contains
anything other than the relevant characters upon calling execve()
(e.g: '   -l  ' is invalid input for wc)
*/
// void	set_cmd_and_option(t_cmd *cmds)
// {
// 	int		i;
// 	char	**cmd_and_opt;
// 	int		is_expanded = 1;
// 	//is_expanded: PLACEHOLDER FOR A VALUE MEANT TO BE IN EACH CMD NODE; NEEDED TO
// 	//DIFFERENTIATE BETWEEN 'ls -l -a -F' and l$VAR, where VAR="s -l -a -F"

// 	if (!cmds)
// 		return ;
// 	while (cmds)
// 	{
// 		if(is_expanded)
// 			cmd_and_opt = ft_split(cmds->full_cmd[0], ' ');
// 		i = 0;
// 		while (cmd_and_opt && cmd_and_opt[i] != NULL)
// 			i++;
// 		alloc_cmd_and_opt(&cmds, i, cmd_and_opt);
// 		free_2d_arr(cmd_and_opt);
// 		cmds = cmds->next;
// 	}
// }

//sets the cmd and option variables in each node of the list of type t_cmd
/*
NOTE TO SELF on ft_strdup: no need to remove whitespaces, because commands
such as wc, ls, and so on will reject flags if the respective string contains
anything other than the relevant characters upon calling execve()
(e.g: '   -l  ' is invalid input for wc)
*/
void	set_c_and_o(t_cmd *cmds)
{
	int		i;
	char	**cmd_and_opt;

	if (!cmds)
		return ;
	while (cmds)
	{
		cmd_and_opt = ft_split(cmds->full_cmd[0], ' ');
		i = 0;
		while (cmd_and_opt && cmd_and_opt[i] != NULL)
			i++;
		alloc_c_and_o(&cmds, i, cmd_and_opt);
		free_2d_arr(cmd_and_opt);
		cmds = cmds->next;
	}
}


//saves the shell command and its options in the cmd node using ft_strdup()
void	alloc_c_and_o(t_cmd **cmd, int n, char **cmd_and_opt)
{
	int	i;
	int	j;

	if (!cmd || !(*cmd) || !(cmd_and_opt) || !(*cmd_and_opt))
		return ;
	i = 0;
	// if (n == 1)
	// {
	// 	(*cmd)->cmd = ft_strdup(cmd_and_opt[0]);
	// 	if ((*cmd)->full_cmd[1] != NULL && is_option((*cmd)->full_cmd[1]))
	// 		(*cmd)->option = ft_strdup((*cmd)->full_cmd[1]);
	// }
	// else if (n == 2)
	// {
	// 	(*cmd)->cmd = ft_strdup(cmd_and_opt[0]);
	// 	(*cmd)->option = ft_strdup(cmd_and_opt[1]);
	// }
	if (n == 1)
	{
		(*cmd)->cmd = ft_strdup(cmd_and_opt[0]);
		while ((*cmd)->full_cmd[i + 1])
			i++;
		(*cmd)->option = malloc(sizeof(char *) * (i + 1));
		if (!(*cmd)->option)
			free_msc_and_errno((*cmd)->msc, "Error in alloc_c_and_o(): ");
		i = 0;
		while ((*cmd)->full_cmd[i + 1])
		{
			(*cmd)->option[i] = ft_strdup((*cmd)->full_cmd[i + 1]);
			if (!(*cmd)->option[i])
			{
				del_split((*cmd)->option, i);
				free_msc_and_errno((*cmd)->msc, "Error in alloc_c_and_o(): ");
			}
			i++;
		}
		(*cmd)->option[i] = NULL;
	}
	else if (n > 1)
	{
		(*cmd)->cmd = ft_strdup(cmd_and_opt[0]);
		while ((*cmd)->full_cmd[i + 1])
			i++;
		(*cmd)->option = malloc(sizeof(char *) * (i + (n - 1) + 1));
		if (!(*cmd)->option)
			free_msc_and_errno((*cmd)->msc, "Error in alloc_c_and_o(): ");
		(*cmd)->option[i + (n - 1)] = NULL;
		i = 0;
		while (cmd_and_opt[i + 1])
		{
			(*cmd)->option[i] = ft_strdup(cmd_and_opt[i + 1]);
			if (!(*cmd)->option[i])
			{
				del_split((*cmd)->option, i);
				free_msc_and_errno((*cmd)->msc, "Error in aloc_c_and_o(): ");
			}
			i++;
		}
		j = 1;
		while ((*cmd)->full_cmd[j])
		{
			(*cmd)->option[i] = ft_strdup((*cmd)->full_cmd[j]);
			if (!(*cmd)->option[i])
			{
				del_split((*cmd)->option, i);
				free_msc_and_errno((*cmd)->msc, "Error in alloc_c_and_o(): ");
			}
			i++;
			j++;
		}
	}
}

//isolates the command part from the path if a command is
//passed as "/bin/ls" or smth similar
void	isolate_cmd(t_cmd **cmd)
{
	int		i;
	int		j;
	char	*res;

	if (!cmd || !(*cmd))
		return ;
	i = 0;
	while ((*cmd)->cmd[i])
	{
		if ((*cmd)->cmd[i] == '/' && (*cmd)->cmd[i + 1])
			j = i + 1;
		i++;
	}
	i = 0;
	while ((*cmd)->cmd[j + i])
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return ;
	i = 0;
	while ((*cmd)->cmd[j])
		res[i++] = ((*cmd)->cmd[j++]);
	free((*cmd)->cmd);
	(*cmd)->cmd = res;
}
