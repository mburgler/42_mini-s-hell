/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 18:34:14 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include "ft_strlen.c"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

// int	main()
// {
// 	char	*s = "12345678";
// 	char	*sub;
// 	// char	*sub2;
// 	int		start;
// 	int		len;
//
// 	start = 15;
// 	len = 10;
// 	sub = ft_substr(s, start, len);
// 	printf("ORIGINAL:123%s\n", sub);
// 	// sub2 = ft_substr(s, start, len);
// 	// printf("MY VERSION:123%s\n", sub2);
// }
