/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:22:50 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/30 18:52:11 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//deletes the 2D array created by lex_split()
void    del_tmp(char **tmp)
{
	int i;

	i = -1;
	if (tmp)
	{
		while (tmp[++i])
		{
			free(tmp[i]);
			tmp[i] = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

//splits the input received by readline() into separate parts,
//and creates a linked list with a node for each individual section
void    input_lexer(t_msc *msc)
{
	char    **tmp;

	if (quote_checker(msc->input) > 0)
		return ;
	tmp = lex_split(msc->input);
	msc->lex = init_lst(msc, tmp);
	if (search_estr(msc->lex) || search_opipe(msc->lex))
		printf("\nOPEN PIPE/EMPTY STRING FOUND\n"); //delete all & print error message instead
	printf("\n\n### TESTING THE LINKED LIST LEXER THING: ###\n\n");
	printf("~~ !! _ symbol added for better readability, not part of the string !! ~~\n\n");
	exp_head(msc); //MATTEO ADDED THIS
	tokenize_op(msc);
	ft_printlist(msc->lex);
	del_tmp(tmp);
}

//ONLY INCLUDED FOR TESTING PURPOSES
void    ft_printlist(t_list *lst)
{
	t_list  *tmp;
	int     i;

	i = 0;
	if (lst)
	{
		tmp = lst;
		while (tmp)
		{
			printf("Node %d contains: _%s_\n", i, tmp->str);
			printf("Quotes: %d\n", tmp->quote_status);
			tmp = tmp->next;
			i++;
		}
	}
}

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

//called in ft_lstnew(); trims the outer quotes of input sections
char	*trim_quotes(const char *s)
{
	int		i;
	int		j;
	char	*ret;
	char	q;

	i = 0;
	while (s[i] != '\0' && s[i] != 34 && s[i] != 39)
		i++;
	q = s[i];
	ret = malloc(sizeof(char) * (ft_strlen(s) - 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != q)
			ret[j++] = s[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

void	set_str(const char *s, char *ret, int *id, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		ret[i] = s[*id + i];
	ret[i] = '\0';
	*id += i;
}