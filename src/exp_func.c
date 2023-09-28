/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:48:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/28 00:36:14 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TO DO
// - handle $?

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
		if (tmp->quote_status == 0 && tmp->str[0] == '$' && tmp->str[1])
		{
			to_free = tmp->str;
			tmp->str = exp_sub(msc, tmp->str + 1, NULL);
			free(to_free);
		}
		else if (tmp->quote_status == 2 && ft_strchr(tmp->str, '$'))
		{
			to_free = tmp->str;
			exp_double_quotes(msc, tmp, placeholder);
			free(to_free);
		}
		tmp = tmp->next;
	}
}

char	*exp_sub(t_msc *msc, char *str, char *to_free_in_case_of_error)
{
	char	*tmp;
	char	*res;

	tmp = getenv(str);
	if (tmp)
		res = ft_strdup(tmp);
	else
		res = ft_strdup("");
	if(!res)
		malloc_error_free_exit(msc, to_free_in_case_of_error, NULL);
	return (res);
}

void	exp_double_quotes(t_msc *msc, t_list *tmp, char *s1)
{
	char	*s2;
	int		i;
	int		j;

	i = 0;
	while (tmp->str[i] && tmp->str[i] != '$')
		i++;
	s1 = ft_substr(tmp->str, 0, i);
	if (!s1)
		malloc_error_free_exit(msc, NULL, NULL);
	if (!tmp->str[++i])
		return (free(s1));
	j = i;
	while(tmp->str[i] && tmp->str[i] != ' ')
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
