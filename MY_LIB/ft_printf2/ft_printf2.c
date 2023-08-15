/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:22 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 21:31:41 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf2.h"

int	g_counter2;

void	ft_putchar_2(char c)
{	
	write (2, &c, 1);
	g_counter2++;
}

void	ft_putnbr_hex_2(unsigned int nbr, char identifier)
{
	char	rev_nbr[8];
	int		index;

	index = 0;
	if (nbr == 0)
		ft_putchar_2('0');
	while (nbr > 0)
	{
		if (identifier == 'x')
			rev_nbr[index] = "0123456789abcdef"[(nbr % 16)];
		else if (identifier == 'X')
			rev_nbr[index] = "0123456789ABCDEF"[(nbr % 16)];
		nbr = nbr / 16;
		index++;
	}
	while (index > 0)
	{
		index--;
		ft_putchar_2(rev_nbr[index]);
	}
}

void	ft_putpointer_hex_2(void *pointer)
{
	unsigned long int	nbr;
	char				rev_nbr[20];
	int					index;

	nbr = (unsigned long int)pointer;
	index = 0;
	if (!nbr)
	{
		ft_putstr_2("(nil)");
		return ;
	}
	ft_putstr_2("0x");
	while (nbr > 0)
	{
		rev_nbr[index] = "0123456789abcdef"[(nbr % 16)];
		nbr = nbr / 16;
		index++;
	}
	while (index > 0)
	{
		index--;
		ft_putchar_2(rev_nbr[index]);
	}
}

void	procent_handler_2(const char *str, va_list arg)
{
	if (*str == 'c')
		ft_putchar_2(va_arg(arg, int));
	else if (*str == 's')
		ft_putstr_2(va_arg(arg, char *));
	else if (*str == 'p')
		ft_putpointer_hex_2(va_arg(arg, void *));
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_2(va_arg(arg, int));
	else if (*str == 'u')
		ft_putnbr_unsigned_2(va_arg(arg, unsigned int));
	else if (*str == 'x' || *str == 'X')
		ft_putnbr_hex_2(va_arg(arg, unsigned int), *str);
	else if (*str == '%')
		ft_putchar_2('%');
}

int	ft_printf_2(const char *str, ...)
{
	va_list	arg;
	int		i;

	g_counter2 = 0;
	va_start(arg, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			procent_handler_2(str + i + 1, arg);
			i++;
		}
		else
			ft_putchar_2(*(str + i));
		i++;
	}
	va_end(arg);
	return (g_counter2);
}

// int	main(void)
// {
// 	void	*pointer = "P";

// 	printf("OFFICIAL OUTPUT:	 \"%c_%%_%s_%i_%d_%u_%x_%X_%s_%%_%p\"\n",
// 'a', "String!", 0x3E6, 0x3E7, 123, 2147483647, 999, "abc", pointer);
// 	ft_printf("MY OUTPUT:	 	  %c_%%_%s_%i_%d_%u_%x_%X_%s_%%_%p\n", 
// 'a', "String!", 0x3E6, 0x3E7, 123, 2147483647, 999, "abc", pointer);
// 	return (0);
// }

/*
va_list is declaring a pointer to the arg list
va_start initializes the arg to the list pinter *arg
*/
