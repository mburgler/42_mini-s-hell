/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:00:02 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/27 21:09:42 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	malloc_error_free_exit(t_msc *msc, char *to_free, char *to_free2)
{
	if (to_free)
		free(to_free);
	if (to_free2)
		free(to_free2);
	write(2, "Error: malloc failed\n", 22);
	free_all(msc);
	exit(1);
}