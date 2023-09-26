/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:49:43 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/26 21:03:24 by abektimi         ###   ########.fr       */
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
    while (i >= 0)
    {
        if (words[i])
            free(words[i]);
        i--;
    }
    free(words);
    return (NULL);
}

int get_wc(const char *s)
{
    int i;
    int wc;

    i = 0;
    wc = 0;
    while (isws(s[i]) && s[i] != '\0')
        i++;
    while (s[i] != '\0')
    {
        if (s[i] == 34 || s[i] == 39)
            skip_quotes(s, &i, &wc);
        if (!isws(s[i]) && !(s[i] == 34 || s[i] == 39))
        {
            while (!isws(s[i]) && s[i] != '\0')
                i++;
            wc++;
        }
        /*if (s[i + 1] == '\0' && !isws(s[i]))
            wc++;*/
        i++;
    }
    return (wc);
}

char    *get_wd(char *s)
{
    int     i;
    int     j;
    char    *ret;

    if (*s == 34 || *s == 39)
        return (get_qt(s, *s));
    i = 0;
    while (!isws(s[i]) && s[i] != '\0')
        i++;
    if (i > 0)
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

char    **lex_split(char *s)
{
    int     i;
    char    **ret;

    if (s == NULL)
        return (NULL);
    ret = malloc(sizeof(char *) * ((get_wc(s) + 1)));
    if (!ret)
        return (NULL);
    i = 0;
    while (*s != '\0')
    {
        while (*s != '\0' && isws(*s))
            s++;
        if (*s != '\0')
        {
            ret[i] = get_wd(s);
            if (!ret[i])
                return (del_split(ret, i));
            i++;
        }
        while (*s != '\0' && !isws(*s))
            s++;
    }
    ret[i] = NULL;
    return (ret);
}