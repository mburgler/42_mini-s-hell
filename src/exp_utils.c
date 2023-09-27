/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:04:43 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/27 21:19:04 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2, char *to_free, char *to_free2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (0);
	while (s1[i++])
		res[i] = s1[i];
	while (s2[j++])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	if(to_free)
		free(to_free);
	if(to_free2)
		free(to_free2);
	return (res);
}