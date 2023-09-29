/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:04:43 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/29 18:04:29 by mburgler         ###   ########.fr       */
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
		return (free_two(to_free, to_free2));
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free_two(to_free, to_free2));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}	
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
		free_two(to_free, to_free2);
	return (res);
}

char	*free_two(char *to_free, char *to_free2)
{
	if (to_free)
		free(to_free);
	if (to_free2)
		free(to_free2);
	return(NULL);
}

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}
