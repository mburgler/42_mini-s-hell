/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:56:22 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/02 15:54:33 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_env(t_msc *msc)
{
	t_env	*tmp;

	tmp = msc->dup_env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		else if (tmp->key && !tmp->value)
			printf("%s=\n", tmp->key);
		tmp = tmp->next;
	}
	g_sig_status = 0;
}
