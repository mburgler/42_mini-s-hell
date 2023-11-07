/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:04:43 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/05 22:32:27 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, char *to_free, char *to_free2)
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

int	ft_trimascii(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		 || (str[i] >= '0' && str[i] <= '9'))
		i++;
	return (i);
}

int	ft_is_whitespace(char *pos, int i)
{
	if ( !pos[i] || pos[i] == ' ' || pos[i] == 9 || pos[i] == 10 || 
		pos[i] == 11 || pos[i] == 12 || pos[i] == 13)
		return (i);
	return (-1);
}

int	ft_is_whitespace_str(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == ' ' && str[i] == 9 && str[i] == 10 && 
			str[i] == 11 && str[i] == 12 && str[i] == 13)
			return (i);
		i++;
	}
	return (-1);
}
