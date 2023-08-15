/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/19 19:40:44 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	helper(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

void	reverse(char *str)
{
	char	temp;
	int		counter;
	int		len;

	counter = -1;
	len = ft_strlen(str);
	while (++counter < len / 2)
	{
		temp = *(str + counter);
		*(str + counter) = *(str + len - 1 - counter);
		*(str + len - 1 - counter) = temp;
	}
}

int	strlen_giver(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	i = 0;
	sign = n < 0;
	str = ft_calloc(strlen_giver(n) + (sign) + 1, sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[i] = '0' + helper(n % 10);
		n /= 10;
		i++;
	}
	if (sign)
		str[i] = '-';
	reverse(str);
	return (str);
}
