/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/09 16:19:51 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <bsd/string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	long unsigned int	i;
	long unsigned int	i2;
	long unsigned int	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (i < len)
	{
		j = 0;
		i2 = i;
		while (big[i2] == little[j] && i2 < len)
		{
			i2++;
			j++;
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}

/*int	main()
{
	char	*little = "12";
	char	*big = "1234125671289";
	char	*pointer;
	char	*pointer2;
	long unsigned int	n;
	long unsigned int	i;

	i = 0;
	n = 9;

	while (i <= n)
	{
    printf("---------size_t is %ld---------\n", i);
	pointer = strnstr(big, little, i);
	printf("OFFICIAL:   %p\n", pointer);

	pointer2 = ft_strnstr(big, little, i);
	printf("MY VERSION: %p\n\n", pointer2);
	i++;
	}
	printf("---------------------\nERROR HANDLING\n
	1. big pointer: %p\n2. little pointer: %p\n", big, little);
}*/
