/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:06:04 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/25 18:06:40 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*shift_lex_for_cmd(t_cmd *cmd, t_list *tmp)
{
	int	i;

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
