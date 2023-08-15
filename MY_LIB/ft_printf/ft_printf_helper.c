/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:15:06 by mburgler          #+#    #+#             */
/*   Updated: 2022/11/21 18:34:39 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return ;
	}
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	int	i;
	int	count;
	int	digit[10];

	count = 0;
	i = nb;
	if (nb < 0)
	{
		ft_putchar('-');
	}
	else if (nb == 0)
		ft_putchar('0');
	else
		i = (nb * (-1));
	while (i <= -1)
	{
		digit[count] = (((i % -10) * -1) + 48);
		i = i / 10;
		count ++;
	}
	while (count > 0)
	{
		count --;
		ft_putchar(digit[count]);
	}
}

void	ft_putnbr_unsigned(unsigned int nb)
{
	unsigned int	i;
	int				count;
	int				digit[10];

	count = 0;
	i = nb;
	if (nb == 0)
		ft_putchar('0');
	i = nb;
	while (i >= 1)
	{
		digit[count] = ((i % 10) + 48);
		i = i / 10;
		count ++;
	}
	while (count > 0)
	{
		count --;
		ft_putchar(digit[count]);
	}
}
