/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:38:40 by mburgler          #+#    #+#             */
/*   Updated: 2023/08/08 18:09:24 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	t_msc *msc;

	msc = ft_calloc(1, sizeof(t_msc));
	if (!msc)
		return (-1);
	if (parsing(argc, argv, msc) == -1)
		return (free_all(msc), -1);
	debug_print_list(msc->list);
	return (0);
}