/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 05:24:27 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/01 18:21:43 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_option(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && isws(str[i]))
		i++;
	if (str[i] == '-')
		return (1);
	return (0);
}