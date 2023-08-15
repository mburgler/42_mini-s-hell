/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:23:12 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*int main()
{
	int	res1;
	int	res2;
	int	c;

	c = 'A';
	res1 = tolower(c);
	res2 = ft_tolower(c);
	printf("ORIGINAL INPUT   : %d\n", c);
    printf("-------------------------\n");
	printf("ORIGINAL FUNTCION: %d\n", res1);
	printf("MY VERSION       : %d\n", res2);
	return (0);
}*/
