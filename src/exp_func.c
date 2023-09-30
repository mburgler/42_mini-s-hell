/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:48:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/30 22:48:53 by mburgler         ###   ########.fr       */
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
			if(abort_when_whitespace(msc, &tmp) == 1)
				continue;
			exp_double_quotes(msc, tmp, placeholder);
			free(to_free);
		}
		// if(ft_strchr(tmp->str, '$')
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
		free_two(env, end);
	//	printf("##str: _%s_\n", str);
		tmp = ft_strdup("");
	}
	printf("##str: _%s_\n", str);
	if(!tmp)
		malloc_error_free_exit(msc, to_free_in_case_of_error, NULL);
	return (tmp);
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
	i = ft_strlen(tmp->str);
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

int	abort_when_whitespace(t_msc *msc, t_list **tmp)
{
	char	*pos;

	pos = (ft_strchr((*tmp)->str, '$') + 1);
	if(!pos || !pos[0] || pos[0] == ' ' || pos[0] == 9 || pos[0] == 10 || 
		pos[0] == 11 || pos[0] == 12 || pos[0] == 13)
	{
		*tmp = (*tmp)->next;
		return(1);
	}
	(void)msc;
	return(0);
}
