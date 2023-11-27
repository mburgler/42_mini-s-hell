/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:08:48 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 14:48:44 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sh_lvl(t_msc *msc)
{
	t_env	*tmp;
	char	*to_free;

	tmp = msc->dup_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			if (sh_lvl_irregular(msc, tmp) == 1)
				return ;
			to_free = tmp->value;
			tmp->value = ft_itoa(ft_atoi(tmp->value) + 1);
			if (!tmp->value)
				malloc_error_free_exit(msc, NULL, NULL);
			free(to_free);
			return ;
		}
		tmp = tmp->next;
	}
	export_core(msc, "SHLVL=1");
}

int	sh_lvl_irregular(t_msc *msc, t_env *tmp)
{
	char	*to_free;

	if (!tmp->value)
	{
		tmp->value = ft_strdup("1");
		if (!tmp->value)
			malloc_error_free_exit(msc, NULL, NULL);
		return (1);
	}
	if (sh_lvl_alph(msc, tmp) == 1)
		return (1);
	if (ft_atoi(tmp->value) < 0 || sh_lvl_overflow(tmp->value) == 1)
	{
		to_free = tmp->value;
		tmp->value = ft_strdup("0");
		if (!tmp->value)
			malloc_error_free_exit(msc, NULL, NULL);
		free(to_free);
		return (1);
	}
	return (0);
}

int	sh_lvl_alph(t_msc *msc, t_env *tmp)
{
	int		i;
	char	*to_free;

	i = 0;
	while (tmp->value[i])
	{
		while (tmp->value[i] && (ft_is_whitespace(tmp->value + i, 0) >= 0 \
			|| tmp->value[i] == '0' || tmp->value[i] == '+' \
			|| tmp->value[i] == '-'))
			i++;
		if (!ft_isdigit(tmp->value[i]))
		{
			to_free = tmp->value;
			tmp->value = ft_strdup("1");
			if (!tmp->value)
				malloc_error_free_exit(msc, NULL, NULL);
			free(to_free);
			return (1);
		}
		i++;
	}
	return (0);
}

int	sh_lvl_overflow(const char *str)
{
	int		i;
	int		len;
	char	*max;

	max = "2147483647";
	i = 0;
	len = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	else if (ft_strncmp(str, max, 10) >= 0)
		return (1);
	else
		return (0);
}
