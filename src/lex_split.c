/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:49:43 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/10 03:19:34 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//returns 1 upon encountering a white space characyer
int	isws(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

//deletes the content of char **words
//up until the most recently initialized index
void	*del_split(char **words, int i)
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
		words = NULL;
	}
	return (NULL);
}

//returns the number of sections in the input string using skip_section()
int	get_wc(const char *s)
{
	int		i;
	int		wc;

	i = 0;
	wc = 0;
	while (s[i] != '\0')
	{
		while (isws(s[i]) && s[i] != '\0')
			i++;
		skip_section(s, &i, &wc, s[i]);
	}
	return (wc);
}

//returns a string which contains one (1)
//contiguous input section using set_word()
char	*get_wd(const char *s, int *i)
{
	int		start;
	char	q;

	start = (*i);
	while (s[*i] != '\0')
	{
		if (s[*i] != 34 && s[*i] != 39)
			while (s[*i] != '\0' && !isws(s[*i]) && s[*i] != 34 && s[*i] != 39)
				(*i)++;
		if (s[*i] == 34 || s[*i] == 39)
		{
			q = s[(*i)++];
			while (s[*i] != '\0' && s[*i] != q)
				(*i)++;
			(*i)++;
		}
		if (isws(s[*i]) || s[*i] == '\0')
			break ;
	}
	return (set_word(s, i, start));
}

//splits the string read by readline() into
//a 2D array for later use in input_lexer()
//each entry in char **ret contains one section of input respectively
char	**lex_split(char *s)
{
	int		i;
	int		j;
	char	**ret;

	ret = set_array(s, get_wc(s));
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
