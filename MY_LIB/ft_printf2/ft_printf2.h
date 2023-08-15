/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:12:46 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 21:16:11 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF2_H
# define FT_PRINTF2_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

void	ft_putnbr_hex_2(unsigned int nbr, char identifier);
void	ft_putpointer_hex_2(void *pointer);
void	procent_handler_2(const char *str, va_list arg);
int		ft_printf_2(const char *str, ...);
void	ft_putchar_2(char c);
void	ft_putstr_2(char *str);
void	ft_putnbr_2(int nb);
void	ft_putnbr_unsigned_2(unsigned int nb);

#endif
