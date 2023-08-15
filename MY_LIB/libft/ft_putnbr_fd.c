/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/10 21:21:41 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	count;
	int	digit[10];

	count = 0;
	i = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
	}
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else
		i = (n * (-1));
	while (i <= -1)
	{
		digit[count] = (((i % -10) * -1) + 48);
		i = i / 10;
		count ++;
	}
	while (count > 0)
	{
		count --;
		ft_putchar_fd(digit[count], fd);
	}
}
