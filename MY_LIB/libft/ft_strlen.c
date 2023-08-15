/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:29:47 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:08:38 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

size_t	ft_strlen(const char *s)
{
	unsigned long int	index;

	index = 0;
	while (s[index] != '\0')
	{
		index++;
	}
	return (index);
}

/*int	main()
{
	const char	*str = "Hallo";
	size_t		len;
	size_t		len2;

	len = ft_strlen(str);
	printf("Length:%ld\n", len);
	len2 = strlen(str);
	printf("Length official:%ld", len2);
}*/