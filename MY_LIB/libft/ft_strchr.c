/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/17 20:40:37 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// int	ascii_int(int c)
// {
// 	while (c > 127)
// 	{
// 		c = c - 128;
// 	}
// 	return (c);
// }

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (NULL);
}

// int	main()
// {
// 	int	c = '2';
// 	char *str = "9876teste54321abcdefstu";
// 	char	*pointer;
// 	char	*pointer2;

//     printf("---------%c---------\n", c);
// 	pointer = strchr(str, c);
// 	printf("OFFICIAL:   %p\n", pointer);

// 	pointer2 = ft_strchr(str, c);
// 	printf("MY VERSION: %p\n\n", pointer2);

//     c = '\0';

//     printf("-----NULL-BYTE-----\n");
//     pointer = strchr(str, 357);
// 	printf("OFFICIAL:   %p\n", pointer);

// 	pointer2 = ft_strchr(str, 357);
// 	printf("MY VERSION: %p\n\n", pointer2);

//     c = 'a';

//     printf("---------%c---------\n", c);
//     pointer = strchr(str, 1024);
// 	printf("OFFICIAL:   %p\n", pointer);

// 	pointer2 = ft_strchr(str, 1024);
// 	printf("MY VERSION: %p\n\n", pointer2);

//     c = 't';

//     printf("---------%c---------\n", c);
//     pointer = strchr(str, ('t' + 256));
// 	printf("OFFICIAL:   %p\n", pointer);

// 	pointer2 = ft_strchr(str, ('t' + 256));
// 	printf("MY VERSION: %p\n\n", pointer2);
// }