/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:49 by abektimi          #+#    #+#             */
/*   Updated: 2023/10/05 21:23:44 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//shows whether the input has open quotes or not,
//by returning one of three possible values:
//i) a value of 0 shows that all quotes are closed
//ii) a value of 1 shows that there are open double-quotes
//iii) a value of 2 shows that there are open single-quotes
int quote_checker(const char *s)
{
	int i;
	int q;

	i = 0;
	q = 0;
	while (s[i] != '\0')
	{
		if (q == 0 && (s[i] == 34 || s[i] == 39))
			q = s[i] % 2 + 1;
		else if (q != 0 && (s[i] == 34 || s[i] == 39))
		{
			if (q == s[i] % 2 + 1)
				q = 0;
		}
		i++;
	}
	return (q);
}

//ensures that different kinds of quoted and unquoted sections in char *s
//are counted as one (1) string section respectively
void	skip_section(const char *s, int *i, int *wc, int id)
{
	if (id != 34 && id != 39)
		while (s[*i] != '\0' && !isws(s[*i]) && s[*i] != 34 && s[*i] != 39)
			(*i)++;
	else if (id == 34)
	{
		(*i)++;
		while (s[*i] != '\0' && s[*i] != 34)
			(*i)++;
		(*i)++;
	}
	else if (id == 39)
	{
		(*i)++;
		while (s[*i] != '\0' && s[*i] != 39)
			(*i)++;
		(*i)++;
	}
	if (isws(s[*i]) || s[*i] == '\0')
			(*wc)++;
}

//uses indices start and end to write from char *s into a new string
char	*set_word(const char *s, int *end, int start)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ((*end) - start);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

//sets the "int quote_status" flag of each t_list node
//0 -> no quotes
//1 -> quotes
int has_quotes(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

//initializes an empty 2D array for later use in lex_spit()
char	**set_array(const char *s)
{
	char	**ret;
	int		i;
	int		wc;

	if (s == NULL)
		return (NULL);
	wc = get_wc(s);
	ret = malloc(sizeof(char *) * (wc + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		ret[i] = NULL;
		i++;
	}
	return (ret);
}