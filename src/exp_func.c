/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:48:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/26 14:57:28 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exp_head(t_msc *msc)
{
	t_list	*tmp;

	if (!msc->lex)
		return ;
	tmp = msc->lex;
	while (tmp && tmp->str)
	{
		tmp->exp = 0;
		if (tmp->quote_status == 0 && tmp->str[0] == '~')
		{
			exp_tilde(msc, tmp);
			tmp = tmp->next;
			continue ;
		}
		if (ft_strchr(tmp->str, '$'))
			exp_logic_new(msc, tmp);
		ft_shift_to_dollar(tmp->str, 1);
		tmp = tmp->next;
	}
	exp_retokenize(msc);
	reset_lex_index(msc->lex);
}

void	exp_logic_new(t_msc *msc, t_list *tmp)
{
	int	i;
	int	a0_end;

	i = 0;
	while (tmp->str[i])
	{
		i = ft_shift_to_dollar(tmp->str, 0);
		if (i == -1)
			return ;
		if (get_quote_status(tmp->str, i) == 1)
			continue ;
		if (tmp->str[i + 1] == '?')
			exp_dol_qmark(msc, tmp, i);
		else
		{
			tmp->exp = 1;
			a0_end = ft_trimascii(tmp->str + i + 1);
			exp_sub(tmp->str, i, a0_end, msc);
		}
	}
}

void	exp_sub(char *str, int i, int a0, t_msc *msc)
{
	char	*env;
	char	*beg;
	char	*end;
	char	*placeholder;

	placeholder = str;
	env = ft_substr(str, i + 1, a0);
	if (!env)
		malloc_error_free_exit(msc, NULL, NULL);
	if (i > 0)
		beg = ft_substr(str, 0, i);
	else
		beg = ft_strdup("");
	if (!beg)
		malloc_error_free_exit(msc, env, NULL);
	if (str[i + a0 + 1] == '\0')
		end = ft_strdup("");
	else
		end = ft_substr(str, i + a0 + 1, ft_strlen(str) - a0 - i);
	if (!end)
		malloc_error_free_exit(msc, beg, env);
	free(placeholder);
	placeholder = ft_getenv(env, msc);
	if (!placeholder)
		placeholder = ft_strdup("");
	else
		placeholder = ft_strdup(placeholder);
	if (!placeholder)
		malloc_error_free_exit(msc, beg, end);
	free(env);
	str = ft_strjoin_free(beg, placeholder, beg, placeholder);
	if (!str)
		malloc_error_free_exit(msc, end, NULL);
	str = ft_strjoin_free(str, end, str, end);
	if (!str)
		malloc_error_free_exit(msc, NULL, NULL);
}

void	exp_dol_qmark(t_msc *msc, t_list *tmp, int i)
{
	char	*to_free;
	char	*code;
	char	*ph;

	to_free = tmp->str;
	code = ft_itoa(g_sig_status);
	if (!code)
		malloc_error_free_exit(msc, NULL, NULL);
	if (i > 0)
		ph = ft_substr(tmp->str, 0, i);
	else
		ph = ft_strdup("");
	if (!ph)
		malloc_error_free_exit(msc, code, NULL);
	tmp->str = ft_strjoin_free(ph, code, ph, code);
	if (to_free[i + 2] == '\0')
		ph = ft_strdup("");
	else
		ph = ft_substr(to_free, i + 2, ft_strlen(to_free) - i - 2);
	if (!ph)
		malloc_error_free_exit(msc, to_free, NULL);
	tmp->str = ft_strjoin_free(tmp->str, ph, tmp->str, ph);
	free(to_free);
}

void	exp_tilde(t_msc *msc, t_list *tmp)
{
	char	*tf;
	char	*env_home;

	tf = tmp->str;
	if (ft_getenv("HOME", msc))
		env_home = ft_getenv("HOME", msc);
	else if (msc->env_home)
		env_home = msc->env_home;
	else
		env_home = "~\0";
	if (tmp->str[1] == '\0')
		tmp->str = ft_strjoin_free(env_home, "", tf, NULL);
	else if (tmp->str[1] == '/')
	{
		tmp->str = ft_strjoin_free(env_home, tmp->str + 1, tf, NULL);
	}
	else
		tmp->str = ft_strjoin_free("~", tmp->str + 1, tf, NULL);
	if (!tmp->str)
		malloc_error_free_exit(msc, tf, NULL);
}
