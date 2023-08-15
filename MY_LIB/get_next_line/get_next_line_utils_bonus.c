/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:02:07 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/06 19:06:18 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft/libft.h"

char	*ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (NULL);
}

int	ft_strlen2(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	if (!s1)
		return (failsafe(s2));
	i = 0;
	j = 0;
	len = ft_strlen2(s1) + ft_strlen2(s2) + 1;
	res = ft_calloc(1, sizeof(char) * len);
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*failsafe(char *str)
{
	int		i;
	char	*result;

	i = ft_strlen2(str);
	result = ft_calloc(1, sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	seek_end_of_line(char *mem)
{
	int	i;

	i = 0;
	while (mem[i] && mem[i] != '\n')
		i++;
	return (i);
}
