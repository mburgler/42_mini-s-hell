/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:46:48 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:10:35 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <bsd/string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int		index;

	if (size > 0)
	{
		index = 0;
		while (src[index] && index < size - 1)
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (ft_strlen(src));
}

/*int	main()
{
	const char	*src = "987654321";
	char	dest1[12] = "123456789123";
	char	dest2[12] = "123456789123";
	size_t len1;
	size_t len2;

	len1 = strlcpy(dest1, src, 4);
	len2 = ft_strlcpy(dest2, src, 4);
	printf("ORIGINAL String %s mit Länge %ld\n", dest2, len1);
	printf("String %s mit Länge %ld\n", dest2, len2);
}*/
