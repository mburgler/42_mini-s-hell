/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:49:43 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/30 18:17:27 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int isws(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void    *del_split(char **words, int i)
{
	if (words)
	{
		while (i >= 0)
		{
			if (words[i])
				free(words[i]);
			i--;
		}
		free(words);
	}
	return (NULL);
}

int get_wc(const char *s)
{
	int i;
	int wc;

	i = 0;
	wc = 0;
	while (s[i] != '\0')
	{
		while (isws(s[i]) && s[i] != '\0')
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			skip_quotes(s, &i);
			wc++;
		}
		else if (s[i] != '\0' && !isws(s[i]) && !(s[i] == 34 || s[i] == 39))
		{
			while (!isws(s[i]) && s[i] != '\0')
				i++;
			wc++;
		}
	}
	return (wc);
}

char    *get_wd(char *s, int *id)
{
	int     i;
	char	q;
	char    *ret;

	if (s[*id] == 34 || s[*id] == 39)
		return (get_qt(s, id, s[*id]));
	i = 0;
	while (!isws(s[*id + i]) && s[*id + i] != '\0')
		i++;
	if (s[*id + i - 1] == 34 || s[*id + i - 1] == 39)
	{
		q = s[*id + i - 1];
		while (s[*id + i] != '\0' && s[*id + i] != q)
			i++;
		i++;
	}
	if (i > 0)
		ret = ft_calloc((i + 1), sizeof(char));
	else
		return (NULL);
	if (!ret)
		return (NULL);
	set_str(s, ret, id, i);
	return (ret);
}

char    **lex_split(char *s)
{
	int     i;
	int		j;
	char    **ret;

	ret = set_array(s);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] != '\0' && isws(s[j]))
			j++;
		if (s[j] != '\0')
		{
			ret[i] = get_wd(s, &j);
			if (!ret[i])
				return (del_split(ret, i));
			i++;
		}
	}
	ret[i] = NULL;
	return (ret);
}