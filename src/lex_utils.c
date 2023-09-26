/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:49 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/26 21:25:24 by abektimi         ###   ########.fr       */
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
void    skip_quotes(const char *s, int *i, int *wc)
{
    char    tmp;

    tmp = s[(*i)++];
    while (s[*i] != '\0' && s[*i] != tmp)
        (*i)++;
    (*i)++;
    if (!isws(s[*i]))
    {
        while (s[*i] != '\0' && !isws(s[*i]))
            (*i)++;
    }
    (*wc)++;
}

//get_qt() returns the input section in quotation marks
//to lex_split() as one cohesive entry 
char    *get_qt(char *s, char q)
{
    int     i;
    int     j;
    char    *ret;

    i = 1;
    while (s[i] != '\0' && s[i] != q)
        i++;
    if (s[i] != '\0' && !isws(s[i]))
        while (s[i] != '\0' && isws(s[i]))
            i++;
    if (i > 1)
        ret = malloc(sizeof(char) * (i + 1));
    else
        return (NULL);
    j = -1;
    if (ret != NULL)
    {
        while (++j < i)
            ret[j] = s[j];
        ret[j] = '\0';
        s += j;
        return (ret);
    }
    return (NULL);
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