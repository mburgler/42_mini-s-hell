/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/19 19:27:35 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include "ft_strlen.c"

int	find_sep(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	give_strlen(const char *str, char *set)
{
	int	n;

	n = 0;
	while (*(str + n) != '\0' && find_sep(*(str + n), set) != 1)
	{
		n++;
	}
	return (n);
}

void	ft_strcpy(char *dest, const char *src, char *set)
{
	int	counter;

	counter = 0;
	while (*(src + counter) != '\0'
		&& find_sep(*(src + counter), set) != 1)
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = '\0';
}

int	tranformer(int count, const char *str, char *set, char **ret)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] != '\0' && (find_sep(str[j], set) == 1))
		j++;
	while (i < count)
	{
		ret[i] = malloc(sizeof(char) * (give_strlen(str + j, set) + 1));
		if (ret[i] == 0)
			return (0);
		ft_strcpy(ret[i], str + j, set);
		i++;
		j = j + give_strlen(str + j, set);
		while (find_sep(*(str + j), set) == 1)
			j++;
	}
	ret[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		counter;
	int		i;
	int		j;
	char	**ret;
	char	sep[2];

	counter = 0;
	i = -1;
	if (!s)
		return (0);
	sep[0] = c;
	sep[1] = '\0';
	while (s[++i])
	{
		if ((find_sep(s[i], sep) == 0 && find_sep(s[i + 1], sep) == 1) || \
			(find_sep(s[i], sep) == 0 && s[i + 1] == '\0'))
			counter++;
	}
	ret = malloc(sizeof(char *) * (counter + 1));
	if (ret == 0)
		return (0);
	j = tranformer(counter, s, sep, ret);
	if (j == 0)
		return (0);
	return (ret);
}

// int      main(void)
// {
// 	char *test = "\0aa\0bbb";
//
// 	char del = '\0';
// 	char **arr = ft_split(test, del);
// 	int	no_elements;
//
// 	while (*arr)
// 	{
// 		printf("-%s-\n", *arr++);
// 	}
// 	printf("-%s-\n", *arr);
// 	printf("-%s-\n", *arr++);
// 	no_elements = count_elements(test, del);
// 	printf("\n--------------\nNO ELEMENTS: %d\n", no_elements);
// }