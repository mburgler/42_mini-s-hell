/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:48:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/01 19:59:16 by abektimi         ###   ########.fr       */
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
	//exp_retokenize(msc);
}

void	exp_logic_new(t_msc *msc, t_list *tmp)
{
	int	i;
	int	aA0_end;

	i = 0;
	while (tmp->str[i])
	{
		i = ft_shift_to_dollar(tmp->str, 0);
		if (i == -1)
			return ;
		if (get_quote_status(tmp->str, i) == 1)
			continue;
		if (tmp->str[i + 1] == '?')
			exp_dol_qmark(msc, tmp, i);
		else
		{
			aA0_end = ft_trimascii(tmp->str + i + 1);
			exp_sub(tmp, i, aA0_end, msc);
		}
	}
}

void	exp_sub(t_list *tmp, int i, int aA0_end, t_msc *msc)
{
	char	*env;
	char	*beg;
	char	*end;
	char	*placeholder;

	placeholder = tmp->str;
	env = ft_substr(tmp->str, i + 1, aA0_end);
	if (!env)
		malloc_error_free_exit(msc, NULL, NULL);
	if (i > 0)
		beg = ft_substr(tmp->str, 0, i);
	else
		beg = ft_strdup("");
	if (!beg)
		malloc_error_free_exit(msc, env, NULL);
	if (tmp->str[i + aA0_end + 1] == '\0')
		end = ft_strdup("");
	else
		end = ft_substr(tmp->str, i + aA0_end + 1, ft_strlen(tmp->str) - aA0_end - i);
	if (!end)
		malloc_error_free_exit(msc, beg, env);
	free(placeholder);
	placeholder = getenv(env);
	if (!placeholder)
		placeholder = ft_strdup("");
	else
		placeholder = ft_strdup(placeholder);
	if (!placeholder)
		malloc_error_free_exit(msc, beg, end);
	free(env);
	tmp->str = ft_strjoin_free(beg, placeholder, beg, placeholder);
	if (!tmp->str)
		malloc_error_free_exit(msc, end, NULL);
	tmp->str = ft_strjoin_free(tmp->str, end, tmp->str, end);
	if (!tmp->str)
		malloc_error_free_exit(msc, NULL, NULL);
}

void	exp_dol_qmark(t_msc *msc, t_list* tmp, int i)
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

	tf = tmp->str;
	if (tmp->str[1] == '\0')
		tmp->str = ft_strjoin_free(msc->env_home, "", tf, NULL);
	else
		tmp->str = ft_strjoin_free(msc->env_home, tmp->str + 1, tf, NULL);
	if (!tmp->str)
		malloc_error_free_exit(msc, tf, NULL);
}

int	ft_shift_to_dollar(char *str, int reboot)
{
	static int	i;

	if (reboot == 1)
	{
		i = 0;
		return (-42);
	}
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != '\"')
		{
			if (ft_is_whitespace(str, i + 1) == -1)
			{
				i++;
				return (i - 1);
			}
		}
		i++;
	}
	return (-1);
}

int	get_quote_status(char *str, int dol_i)
{
	int	i;

	i = 0;
	while (str[i] && i < dol_i)
	{
		if (str[i] == '\"')
			return (2);
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && i < dol_i)
			{
				if (str[i] == '\'')
					return (0);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
