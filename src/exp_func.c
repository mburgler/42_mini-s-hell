/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:48:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 15:47:51 by mburgler         ###   ########.fr       */
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
			tmp->str = exp_logic_new(msc, tmp->str, tmp);
		ft_shift_to_dollar(tmp->str, 1);
		tmp = tmp->next;
	}
	exp_retokenize(msc);
	reset_lex_index(msc->lex);
}

char	*exp_logic_new(t_msc *msc, char *str, t_list *tmp)
{
	int	i;
	int	a0_end;

	i = 0;
	while (str[i])
	{
		i = ft_shift_to_dollar(str, 0);
		if (i == -1)
		{
			return (str);
		}
		if (get_quote_status(str, i) == 1)
			continue ;
		if (str[i + 1] == '?')
			str = exp_dol_qmark(msc, str, i);
		else
		{
			if (tmp)
				tmp->exp = 1;
			a0_end = ft_trimascii(str + i + 1);
			str = exp_sub(str, i, a0_end, msc);
		}
	}
	free_msc_and_exit(msc, "expander error");
	return (NULL);
}

char	*exp_sub(char *str, int i, int a0, t_msc *msc)
{
	t_exp	*exp;

	exp = exp_sub_init(str, i, a0, msc);
	exp->buff = ft_getenv(exp->env, msc);
	if (!exp->buff)
		exp->buff = ft_strdup("");
	else
		exp->buff = ft_strdup(exp->buff);
	if (!exp->buff)
		malloc_error_free_exp_exit(msc, exp, exp->beg, exp->end);
	free(exp->env);
	str = ft_strjoin_free(exp->beg, exp->buff, exp->beg, exp->buff);
	if (!str)
		malloc_error_free_exp_exit(msc, exp, exp->end, NULL);
	str = ft_strjoin_free(str, exp->end, str, exp->end);
	if (!str)
		malloc_error_free_exp_exit(msc, exp, NULL, NULL);
	free(exp);
	return (str);
}

char	*exp_dol_qmark(t_msc *msc, char *str, int i)
{
	char	*to_free;
	char	*code;
	char	*ph;

	to_free = str;
	code = ft_itoa(g_sig_status);
	if (!code)
		malloc_error_free_exit(msc, NULL, NULL);
	if (i > 0)
		ph = ft_substr(str, 0, i);
	else
		ph = ft_strdup("");
	if (!ph)
		malloc_error_free_exit(msc, code, NULL);
	str = ft_strjoin_free(ph, code, ph, code);
	if (to_free[i + 2] == '\0')
		ph = ft_strdup("");
	else
		ph = ft_substr(to_free, i + 2, ft_strlen(to_free) - i - 2);
	if (!ph)
		malloc_error_free_exit(msc, to_free, NULL);
	str = ft_strjoin_free(str, ph, str, ph);
	free(to_free);
	return (str);
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
