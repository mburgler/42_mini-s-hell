/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:48:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/01 02:52:38 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exp_head(t_msc *msc)
{
	t_list	*tmp;
	char	*to_free;
	char	*placeholder;

	placeholder = NULL;
	tmp = msc->lex;
	while (tmp && tmp->str)
	{
		if (tmp->quote_status == 0 && tmp->str[0] == '~')
			exp_tilde(msc, tmp);
		if ((tmp->quote_status == 0 || tmp->quote_status == 2) && ft_strchr(tmp->str, '$'))
		{
			to_free = tmp->str;
			exp_logic(msc, tmp, placeholder, to_free);
		}
		if(ft_shift_to_dollar(tmp->str) == -1)
			tmp = tmp->next;
	}
}

char	*exp_sub(t_msc *msc, char *str, char *to_free_in_case_of_error)
{
	char	*tmp;
	char	*end;
	int		aA0_end;
	char	*env;

	aA0_end = ft_trimascii(str);
	env = ft_substr(str, 0, aA0_end);
	if(!env)
		malloc_error_free_exit(msc, to_free_in_case_of_error, NULL);
	end = ft_substr(str, aA0_end, ft_strlen(str) - aA0_end);
	if(!end)
		malloc_error_free_exit(msc, to_free_in_case_of_error, env);
	tmp = getenv(env);
	if (tmp)
		tmp = ft_strjoin_and_free(tmp, end, env, end); //ft_strdup(tmp);
	else
	{
		printf("str%s\n", end);
		free_two(env, end);
		tmp = ft_strdup("");
	}
	if(!tmp)
		malloc_error_free_exit(msc, to_free_in_case_of_error, NULL);
	return (tmp);
}

void	exp_logic(t_msc *msc, t_list *tmp, char *s1, char *to_free)
{
	char	*s2;
	int		i;
	int		j;

	i = ft_shift_to_dollar(tmp->str);
	if(!tmp->str[i] || i == -1)
		return ;
	s1 = ft_substr(tmp->str, 0, i);
	if (!s1)
		malloc_error_free_exit(msc, NULL, NULL);
	if (!tmp->str[++i])
		return (free(s1));
	j = i;
	while(tmp->str[i] && ft_is_whitespace(tmp->str, i) != 1)
		i++;
	s2 = exp_sub(msc, ft_substr(tmp->str, j, i - j), s1);
	s1 = ft_strjoin_and_free(s1, s2, s1, s2);
	if(!s1)
		malloc_error_free_exit(msc, NULL, NULL);
	s2 = ft_substr(tmp->str, i, ft_strlen(tmp->str) - i);
	if(!s2)
		malloc_error_free_exit(msc, s1, NULL);
	tmp->str = ft_strjoin_and_free(s1, s2, s1, s2);
	if(!tmp->str)
		malloc_error_free_exit(msc, s1, s2);
	free(to_free);
}

void	exp_tilde(t_msc *msc, t_list *tmp)
{
	if (tmp->str[1] == '\0')
		tmp->str = ft_strjoin_and_free(msc->env_home, "", tmp->str, NULL);
	else
		tmp->str = ft_strjoin_and_free(msc->env_home, tmp->str + 1, tmp->str, NULL);
	if(!tmp->str)
		malloc_error_free_exit(msc, tmp->str, NULL);
}

int	ft_shift_to_dollar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
		{
			if(ft_is_whitespace(str, i + 1) == 0 && str[i + 1] != '$')
				return(i);
		}
		i++;
	}
	return(-1);
}
