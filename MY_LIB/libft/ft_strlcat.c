/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:17:34 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/12 17:40:18 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <bsd/string.h>
// #include "ft_strlen.c"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long int	len_src;
	unsigned long int	len_dst;
	unsigned int		i_src;
	unsigned int		i_dst;

	if (!dst && size == 0)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	i_src = 0;
	i_dst = len_dst;
	if (size > 0 && size > len_dst)
	{
		while ((src[i_src] != '\0') && (i_src < (size - len_dst - 1)))
		{
			dst[i_dst] = src[i_src];
			i_src++;
			i_dst++;
		}
		dst[i_dst] = '\0';
		return (len_src + len_dst);
	}
	else
		return (len_src + size);
}

// int	main()
// {
// 	const char	*src = "";
// 	char	dest1[100] = "";
// 	char	dest2[100] = "";
// 	size_t len1;
// 	size_t len2;

// 	len1 = strlcat(dest1, src, 9);
// 	len2 = ft_strlcat(dest2, src, 9);
// 	printf("ORIGINAL String %s mit Länge %ld\n", dest2, len1);
// 	printf("THE NEW  String %s mit Länge %ld\n", dest2, len2);
// }
