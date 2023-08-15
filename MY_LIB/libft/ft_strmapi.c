/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:14:20 by mburgler          #+#    #+#             */
/*   Updated: 2022/10/10 21:48:52 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned long int	len;
	unsigned long int	i;
	char				*ret;

	i = -1;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	while (++i < len)
		ret[i] = f(i, s[i]);
	ret[i] = '\0';
	return (ret);
}

//(char*)malloc(sizeof(char) * len + 1);
//zweites char* erstellt Speicherplatz mit Länge char
//erstes char* teilt den schon erstellten Speicherplatz ein auf Länge char