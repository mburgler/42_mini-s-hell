/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/09 18:39:42 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	long unsigned int	i;
	unsigned char		*temp1;
	unsigned char		*temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (temp1[i] > temp2[i])
			return (temp1[i] - temp2[i]);
		else if (temp1[i] < temp2[i])
			return (temp1[i] - temp2[i]);
		i++;
	}
	return (0);
}

/*int	main()
{
	char	*s1 = "000jksrhdgouijsdhgasditg";
	char	*s2 = "0hefks";
	int	res;
	int	res2;
	int	n = 0;
	int	goal = 9;

	while (n < goal)
	{
		printf("------ FOR %d ------\n", n);
		res = memcmp(s1, s2, n);
		printf("OFFICIAL:   %d\n", res);

		res2 = ft_memcmp(s1, s2, n);
		printf("MY VERSION: %d\n\n", res2);
		n++;
	}
}*/
