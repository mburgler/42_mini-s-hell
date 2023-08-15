/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/12 18:24:50 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*temp;

	temp = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < (n - 1))
	{
		if (temp[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	if (temp[i] == (unsigned char)c)
		return ((void *)s + i);
	return (NULL);
}

/*int	main()
{
	int	c = '2';
    unsigned int	s = 4;
	char *str = "9872654321abc";
	char	*pointer;
	char	*pointer2;
	
    printf("---------%c---------\n", c);
	pointer = memchr(str, c, s);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_memchr(str, c, s);
	printf("MY VERSION: %p\n\n", pointer2);

    c = '\0';

    printf("-----NULL-BYTE-----\n");
    pointer = memchr(str, c, s);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_memchr(str, c, s);
	printf("MY VERSION: %p\n\n", pointer2);

    c = 'a';

    printf("---------%c---------\n", c);
    pointer = memchr(str, c, s);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_memchr(str, c, s);
	printf("MY VERSION: %p\n\n", pointer2);

    c = '2';

    printf("---------%c---------\n", c);
    pointer = memchr(str, c, s);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_memchr(str, c, s);
	printf("MY VERSION: %p\n\n", pointer2);
}*/
