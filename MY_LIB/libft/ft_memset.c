/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:09:25 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*temp;

	temp = s;
	i = 0;
	while (i < n)
	{
		temp[i] = c;
		i++;
	}
	return (s);
}

/*int	main()
{
	char	str1[15] = "Hallo1wie gehts";
    char	str2[15] = "Hallo1wie gehts";
	int	c;
	size_t n;

	c = '0';
	n = 5;

    memset(str1, c, n * sizeof(char));
	printf("%s\n", str1);
	ft_memset(str2, c, n * sizeof(char));
	printf("%s", str2);
}*/
