/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/17 20:41:50 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

/*int	main()
{
	int	c = '2';
	char *str = "987a654321abc987654321abc";
	char	*pointer;
	char	*pointer2;
	
    printf("---------%c---------\n", c);
	pointer = strrchr(str, c);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_strrchr(str, c);
	printf("MY VERSION: %p\n\n", pointer2);

    c = '\0';

    printf("-----NULL-BYTE-----\n");
    pointer = strrchr(str, c);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_strrchr(str, c);
	printf("MY VERSION: %p\n\n", pointer2);

    c = 'a';

    printf("---------%c---------\n", c);
    pointer = strrchr(str, c);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_strrchr(str, c);
	printf("MY VERSION: %p\n\n", pointer2);

    c = '2';

    printf("---------%c---------\n", c);
    pointer = strrchr(str, c);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_strrchr(str, c);
	printf("MY VERSION: %p\n\n", pointer2);
}*/