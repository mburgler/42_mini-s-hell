/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:10:18 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char				*memdst;
	char				*memsrc;
	long unsigned int	append;

	memdst = (char *)dst;
	memsrc = (char *)src;
	if ((memdst == NULL) && (memsrc == NULL))
		return (dst);
	if (src < dst)
	{
		append = n - 1;
		memsrc = memsrc + append;
		memdst = memdst + append;
		while (n--)
			*memdst-- = *memsrc--;
	}
	else if (src >= dst)
	{
		while (n--)
			*memdst++ = *memsrc++;
	}
	return (dst);
}

/*int	main()
{
	char	dest[100] = "abcdefghijklmnopqrstuvwxyz.";

	char	dest2[100] = "abcdefghijklmnopqrstuvwxyz.";

	memmove(dest+10, dest+8, 5);
	printf("Das ist Output 1: %s\n", dest);
	printf("\n");
	ft_memmove(dest2+10, dest2+8, 5);
	printf("Das ist Output 2: %s\n", dest2);
}*/
