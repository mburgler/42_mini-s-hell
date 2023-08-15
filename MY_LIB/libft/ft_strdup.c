/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/09 22:34:22 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <unistd.h>
//#include "ft_strlen.c"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*pointer;
	int		len;

	i = 0;
	len = ft_strlen(s) + 1;
	pointer = malloc(sizeof(char) * len);
	if (pointer == NULL)
		return (NULL);
	while (s[i])
	{
		pointer[i] = s[i];
		i++;
	}
	pointer[i] = '\0';
	return (pointer);
}

/*int	main()
{
	char	*s = "12345678";
	char	*res1;
	char	*res2;
	int		len;
	char	nullbyte_a;

	res1 = strdup(s);
	printf("ORGINAL:      %s\n", res1);
	res2 = ft_strdup(s);
	len = ft_strlen (res2);
	printf("MY VERSION:   %s\n\n", res2);
	printf("with length:  %d\n", len);
	nullbyte_a = res2[8];
	printf("nullbyte:     %c\n", nullbyte_a + 97);
}*/