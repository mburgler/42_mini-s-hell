/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 18:36:41 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include "ft_strlen.c"
// #include "ft_substr.c"
// #include <stdio.h>

int	inset(char str_c, char const *set)
{
	unsigned long int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == str_c)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned long int	beginning;
	unsigned long int	end;
	char				*res;

	if (!s1 || !set)
		return (NULL);
	beginning = 0;
	while (s1[beginning] && inset(s1[beginning], set))
		beginning++;
	end = ft_strlen(s1);
	while ((end > beginning) && inset(s1[end - 1], set))
		end--;
	res = ft_substr(s1, beginning, (end - beginning));
	if (res == NULL)
		return (NULL);
	return (res);
}

// int	main()//int argc, char **argv)
// {
// 	char    *str = "  \t \t \n   \n\n\n\t";
// 	char    *cut = " \n\t";
// 	char    *res;

// 	// if (argc < 2)
// 	// 	return 0;
// 	res = ft_strtrim(str, cut);//argv[1], argv[2]);
// 	printf("Output: %s", res);
// 	return (0);
// }
