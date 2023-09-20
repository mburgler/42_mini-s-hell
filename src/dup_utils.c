/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:15:44 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/20 17:37:43 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_arrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_dup_arr(char **strs)
{
	int	i;
	char	**new;

	i = 0;
	if(!strs || strs[0] == NULL)
		return (NULL);
	new = ft_calloc(ft_arrlen(strs) + 1, sizeof(char *));
	if(!new)
		return (NULL);
	while (strs[i])
	{
		new[i] = ft_strdup(strs[i]);
		if(!new[i])
		{
			ft_free_arr(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}
