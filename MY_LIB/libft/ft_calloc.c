/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:15:17 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h> 
//#include <stdio.h>
//#include "ft_bzero.c"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*pointer;

	pointer = malloc(nmemb * size);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, nmemb * size);
	return (pointer);
}

/*int	main()
{
	size_t	count;
	size_t	size;
	char				*pointer1;
	char				*pointer2;
	int			i;
	int			j; 

	count = 0;
	size = 0;
	pointer1 = calloc(count, size);
	pointer2 = ft_calloc(count, size);
	i = 0;
	j = 0;
	while (pointer1[i] == 0)
	{
		i++;
	}
	while (pointer2[j] == 0)
	{
		j++;
	}
	printf("ORIGINAL:      %d\n", i);
	printf("MY VERSION:    %d\n", j);
}*/
