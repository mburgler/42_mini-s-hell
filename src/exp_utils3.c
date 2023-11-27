/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:34:39 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 15:47:26 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	malloc_error_free_exp_exit(t_msc *msc, t_exp *exp, char *tf, char *tf2)
{
	if (tf)
		free(tf);
	if (tf2)
		free(tf2);
	if (exp)
		free(exp);
	perror("Memory allocation error: malloc\n");
	if (msc)
		free_all(msc);
}

t_exp	*exp_sub_init(char *str, int i, int a0, t_msc *msc)
{
	t_exp	*exp;

	exp = malloc(sizeof(t_exp));
	exp->buff = str;
	exp->env = ft_substr(str, i + 1, a0);
	if (!exp->env)
		malloc_error_free_exp_exit(msc, exp, NULL, NULL);
	if (i > 0)
		exp->beg = ft_substr(str, 0, i);
	else
		exp->beg = ft_strdup("");
	if (!exp->beg)
		malloc_error_free_exp_exit(msc, exp, exp->env, NULL);
	if (str[i + a0 + 1] == '\0')
		exp->end = ft_strdup("");
	else
		exp->end = ft_substr(str, i + a0 + 1, ft_strlen(str) - a0 - i);
	if (!exp->end)
		malloc_error_free_exp_exit(msc, exp, exp->beg, exp->env);
	free(exp->buff);
	return (exp);
}
