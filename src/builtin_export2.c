/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:13:35 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/14 17:32:42 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*check_if_known_var(t_msc *msc, char *str)
{
	t_env	*tmp;
	char	c;
	int		i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	c = str[i];
	tmp = msc->dup_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, str, ft_strchr_i(str, c)) == 0
			&& !tmp->key[ft_strchr_i(str, c)])
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_export_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				str);
			g_sig_status = 1;
			return (1);
		}
		i++;
	}
	if ((str[i] == '+' && str[i + 1] != '=') || ft_isdigit(str[0])
		|| str[0] == '=' || str[0] == '+')
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n",
			str);
		g_sig_status = 1;
		return (1);
	}
	return (0);
}
