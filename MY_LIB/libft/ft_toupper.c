/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/09 16:19:44 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*int	main()
{
	int	res1;
	int	res2;
	int	c;

	c = '0';
	res1 = toupper(c);
	res2 = ft_toupper(c);
	printf("ORIGINAL INPUT   :   %d\n", c);
	printf("ORIGINAL FUNTCION:   %d\n", res1);
	printf("MY VERSION       : %d\n", res2);
	return (0);
}*/
