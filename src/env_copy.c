/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:40:53 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/01 20:29:46 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// //kill getenv
// //change free_stuff.c line 24 & 64

// t_env	*dup_env_head(t_msc *msc, char **org_env)
// {
// 	t_env	*dup_env;

// 	dup_env = malloc(sizeof(t_env));
// 	if(!dup_env)
// 		dup_env_error(msc);
// 	return(dup_env);
// }

// void	*dup_env_error(t_msc *msc)
// {
// 	free(msc);
// 	exit(1);
// }