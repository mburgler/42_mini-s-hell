/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/14 18:28:27 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include "ft_strncmp.c"
// #include "ft_strlen.c"

int	overflow_handler(const char *str, int i, int sign)
{
	int		len;
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	len = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	if (len > 19)
		return (1);
	else if (len < 19)
		return (0);
	else if (sign < 0 && ft_strncmp(str + (i - len), min, 19) > 0)
		return (1);
	else if (sign > 0 && ft_strncmp(str + (i - len), max, 19) > 0)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		nb;

	nb = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] == ' ') || (nptr[i] == '\f') || (nptr[i] == '\n') || \
		(nptr[i] == '\r') || (nptr[i] == '\t') || (nptr[i] == '\v'))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (sign > 0 && overflow_handler(nptr, i, sign))
		return (-1);
	else if (sign < 0 && overflow_handler(nptr, i, sign))
		return (0);
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{	
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	nb = (nb * sign);
	return (nb);
}

// int	main(int argc, char **argv)
// {
// 	const char	*str = argv[1];
// 	int			res1;
// 	int 		res2;

// 	(void)argc;
// 	res1 = atoi(str);
// 	printf("ORIGINAL:   %d\n", res1);
// 	res2 = ft_atoi(str);
// 	printf("MY VERSION: %d", res2);
// }