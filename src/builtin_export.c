/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:13:35 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/08 17:50:17 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_export_head(t_msc *msc, t_cmd *cmd)
{
	int		i;

	i = 1;
	g_sig_status = 0;
	if (!cmd->full_cmd || !cmd->full_cmd[1])
	{
		ft_printf("\nH0n3stly, w3 d0n't car3 ab0ut that, n3ith3r sh0uld y0u.");
		ft_printf("\n\nL0ts of l0v3,\nAl3x and Matt30\n\n");
		return ;
	}
	while (cmd->full_cmd[i])
	{
		if (check_export_syntax(cmd->full_cmd[i])
			|| !ft_strchr(cmd->full_cmd[i], '='))
			return ;
		export_core(msc, cmd->full_cmd[i]);
		i++;
	}
}

void	export_core(t_msc *msc, char *str)
{
	t_env	*known_var;
	char	*tmp;

	if (!str)
		return ;
	known_var = check_if_known_var(msc, str);
	if (known_var == NULL)
	{
		tmp = remove_plus(str);
		if(!tmp)
			free_msc_and_exit(msc, "malloc error");
		export_new(msc, tmp);
		free(tmp);
	}
	else
		export_known(msc, str, known_var);
}

char *remove_plus(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i] == '+')
	{
		ret = ft_substr(str, 0, i);
		if (!ret)
			return (NULL);
		if (!str[i + 2])
			ret = ft_strjoin_free(ret, "=", ret, NULL);
		else
			ret = ft_strjoin_free(ret, str + i + 1, ret, NULL);
		if (!ret)
			return (NULL);
		return (ret);
	}
	return (ft_strdup(str));
}

void	export_new(t_msc *msc, char *str)
{
	t_env	*tmp;

	tmp = ft_dup_envnew(str, msc);

	if (!msc->dup_env)
	{
		msc->dup_env = tmp;
		g_sig_status = 0;
		return ;
	}
	else
	{
		ft_envadd_back(&msc->dup_env, tmp);
		g_sig_status = 0;
		return ;
	}
}

void	export_known(t_msc *msc, char *str, t_env *node)
{
	int		i_split;
	char	*tmp;

	i_split = ft_strchr_i(str, '=');
	if (i_split == -1)
		return ;
	tmp = node->value;
	g_sig_status = 0;
	if (str[i_split - 1] == '+' && (int)ft_strlen(str) > i_split + 1
		&& node->value)
		node->value = ft_strjoin(node->value, str + i_split + 1);
	else if (str[i_split - 1] == '+' && (int)ft_strlen(str) == i_split + 1)
		return ;
	else if((int)ft_strlen(str) > i_split + 1)
		node->value = ft_substr(str, i_split + 1, ft_strlen(str) - i_split);
	else
	{
		if (node->value)
			free(node->value);
		return ;
	}
	if (!node->value)
		free_msc_and_exit(msc, "malloc error");
	free(tmp);
}

t_env	*check_if_known_var(t_msc *msc, char *str)
{
	t_env	*tmp;
	char 	c;
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

//DONE
// += ; might clash
/*
bash-3.2$ export TEST="hallo wie gehts"
bash-3.2$ echo $TEST
hallo wie gehts
bash-3.2$ export TEST=$TEST$TEST$TEST
bash-3.2$ echo $TEST
hallo wie gehtshallo wie gehtshallo wie gehts
-> funktioniert beim expanden. 
LÖSUNG: Regel beim Re-split: nur wenn davor kein export war (achtung falls davor nichts gibt)
*/