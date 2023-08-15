/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/09 19:27:21 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	long unsigned int		i;
	unsigned char			*temp_dest;
	unsigned const char		*temp_src;

	temp_dest = dest;
	temp_src = src;
	if (temp_dest == NULL && temp_src == NULL)
		return (dest);
	i = 0;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

/*int	main()
{
	char	src[100] = "Das ist 000000000000.";
	char	dest[100] = "Das ist 111111111111111.";

	char	src2[100] = "Das ist 000000000000.";
	char	dest2[100] = "Das ist 111111111111111.";

	memcpy(dest+12, src+12, 2);
	printf("Das ist Output 1: %s\n", dest);
	ft_memcpy(dest2+12, src2+12, 2);
	printf("Das ist Output 1: %s\n", dest2);
}*/
