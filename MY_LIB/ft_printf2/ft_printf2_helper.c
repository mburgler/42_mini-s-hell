/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:15:06 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 21:21:49 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf2.h"

void	ft_putstr_2(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_2("(null)");
		return ;
	}
	while (str[i] != '\0')
	{
		ft_putchar_2(str[i]);
		i++;
	}
}

void	ft_putnbr_2(int nb)
{
	int	i;
	int	count;
	int	digit[10];

	count = 0;
	i = nb;
	if (nb < 0)
	{
		ft_putchar_2('-');
	}
	else if (nb == 0)
		ft_putchar_2('0');
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
		ft_putchar_2(digit[count]);
	}
}

void	ft_putnbr_unsigned_2(unsigned int nb)
{
	unsigned int	i;
	int				count;
	int				digit[10];

	count = 0;
	i = nb;
	if (nb == 0)
		ft_putchar_2('0');
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
		ft_putchar_2(digit[count]);
	}
}
