/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:12:07 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/04 15:28:32 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
void	ft_putchar(char c)
{	
	write (1, &c, 1);
}

int	main()
{
	char	str;
	int	return_value;

	str = '1';
	return_value = ft_isalpha(str);
	ft_putchar(return_value + 48);
	return (0);
}*/
