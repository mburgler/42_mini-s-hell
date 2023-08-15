/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/09 16:22:16 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*temp;

	temp = s;
	i = 0;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

/*int	main()
{
	char	str[100] = "Hallo wie gehts";
    char	string[100] = "Mir gehts gut";
    int n;

	n = 5;

	printf("%s\n", str);
    bzero(str+2, n * sizeof(char));
    printf("%s\n", str);
	ft_bzero(string+3, n * sizeof(char));
	printf("%s\n", string);
}*/
