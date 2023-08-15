/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:22 by mburgler          #+#    #+#             */
/*   Updated: 2022/11/21 19:47:07 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_counter;

void	ft_putchar(char c)
{	
	write (1, &c, 1);
	g_counter++;
}

void	ft_putnbr_hex(unsigned int nbr, char identifier)
{
	char	rev_nbr[8];
	int		index;

	index = 0;
	if (nbr == 0)
		ft_putchar('0');
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
		ft_putchar(rev_nbr[index]);
	}
}

void	ft_putpointer_hex(void *pointer)
{
	unsigned long int	nbr;
	char				rev_nbr[20];
	int					index;

	nbr = (unsigned long int)pointer;
	index = 0;
	if (!nbr)
	{
		ft_putstr("(nil)");
		return ;
	}
	ft_putstr("0x");
	while (nbr > 0)
	{
		rev_nbr[index] = "0123456789abcdef"[(nbr % 16)];
		nbr = nbr / 16;
		index++;
	}
	while (index > 0)
	{
		index--;
		ft_putchar(rev_nbr[index]);
	}
}

void	procent_handler(const char *str, va_list arg)
{
	if (*str == 'c')
		ft_putchar(va_arg(arg, int));
	else if (*str == 's')
		ft_putstr(va_arg(arg, char *));
	else if (*str == 'p')
		ft_putpointer_hex(va_arg(arg, void *));
	else if (*str == 'd' || *str == 'i')
		ft_putnbr(va_arg(arg, int));
	else if (*str == 'u')
		ft_putnbr_unsigned(va_arg(arg, unsigned int));
	else if (*str == 'x' || *str == 'X')
		ft_putnbr_hex(va_arg(arg, unsigned int), *str);
	else if (*str == '%')
		ft_putchar('%');
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;

	g_counter = 0;
	va_start(arg, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			procent_handler(str + i + 1, arg);
			i++;
		}
		else
			ft_putchar(*(str + i));
		i++;
	}
	va_end(arg);
	return (g_counter);
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
