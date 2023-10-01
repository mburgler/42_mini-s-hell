/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:49 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/30 18:25:12 by abektimi         ###   ########.fr       */
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

//ensures that sections in the user input which are put in quotes
// are counted as one contiguous entry, including possible whitespace chars
void    skip_quotes(const char *s, int *i)
{
	char    tmp;

	tmp = s[(*i)++];
	while (s[*i] != '\0' && s[*i] != tmp)
		(*i)++;
	if (s[*i] == tmp)
	{
		(*i)++;
		if (!isws(s[*i]) && s[*i] != '\0')
		{
			while (s[*i] != '\0' && !isws(s[*i]))
				(*i)++;
		}
	}
}

//get_qt() returns the input section in quotation marks
//to lex_split() as one cohesive entry 
char    *get_qt(char *s, int *id, char q)
{
	int     i;
	char    *ret;

	i = 1;
	while (s[*id + i] != '\0' && s[*id + i] != q)
		i++;
	if (s[*id + i + 1] != '\0' && !isws(s[*id + i + 1]))
		while (s[*id + i] != '\0' && !isws(s[*id + i]))
			i++;
	else
		i++;
	if (i > 1)
		ret = ft_calloc((i + 1), sizeof(char));
	else
		return (NULL);
	if (!ret)
		return (NULL);
	set_str(s, ret, id, i);
	return (ret);
}

//sets the "int quote_status" flag of each t_list node
//0 -> no quotes
//1 -> single-quotes
//2 -> double-quotes
int s_or_d(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34)
			return (2);
		else if (s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}