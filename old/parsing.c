/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:39:14 by mburgler          #+#    #+#             */
/*   Updated: 2023/08/08 18:12:19 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing(int i_args, char **strs, t_msc *msc)
{
	int i;

	i = 1;
	while (i < i_args)
	{
		if (ft_isvalidstr(strs[i]))
			ft_lstadd_back(&msc->list, ft_lstnew(strs[i]));
		else
			return (ft_printf("minishell: syntax error near unexpected token `%s'\n", strs[i]), -1);
		i++;
	}
	if (!ft_isvalidlist(msc->list))
		return (ft_printf("minishell: syntax error near unexpected token `|'\n"), -1);
	if (!ft_isvalidcmd(msc->list))
		return (ft_printf("minishell: syntax error near unexpected token `|'\n"), -1);
	if (!ft_isvalidpipe(msc->list))
		return (ft_printf("minishell: syntax error near unexpected token `|'\n"), -1);
	if (!ft_isvalidredir(msc->list))
		return (ft_printf("minishell: syntax error near unexpected token `|'\n"), -1);
	return (0);
}

//COPILOT ACCEPTED
int	ft_isvalidstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isvalidchar(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isvalidchar(char c)
{
	if (ft_iswhitespace(c) || ft_isquote(c) || ft_isseparator(c))
		return (0);
	return (1);
}

int		ft_isseparator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int		ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

//COPILOT BS

int	ft_isvalidlist(t_list *list)
{
	while (list)
	{
		if (!ft_isvalidstr(list->str))
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_isvalidcmd(t_list *list)
{
	while (list)
	{
		if (ft_isseparator(list->str[0]))
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_isvalidpipe(t_list *list)
{
	while (list)
	{
		if (list->str[0] == '|')
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_isvalidredir(t_list *list)
{
	while (list)
	{
		if (list->str[0] == '>' || list->str[0] == '<')
			return (0);
		list = list->next;
	}
	return (1);
}

//no space with | or > or >>