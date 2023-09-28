/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:17:00 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/28 23:14:04 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*TO DO

*/

void	pars_head(t_msc *msc)
{
	int	node_nb;

	node_nb = 0;
	while(node_nb != -1)
	{
		node_nb = pars_list(msc);
	}
}

int	pars_list(t_mas *msc)