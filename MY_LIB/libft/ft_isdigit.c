/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:19 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/11 21:07:03 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*void    ft_putchar(char c)                                         
{                                                                               
    write (1, &c, 1);                                                           
}                                                                               
                                                                                
int main()                                                                      
{                                                                               
    char    str;                                                                
    int return_value;                                                           
                                                                                
    str = 'a';                                                                  
    return_value = ft_isdigit(str);                                             
    ft_putchar(return_value + 48);                                              
    return (0);                                                                 
}*/
