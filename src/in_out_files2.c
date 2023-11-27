/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:06:04 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 14:48:16 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*shift_lex_for_cmd(t_cmd *cmd, t_list *tmp)
{
	int	i;

	i = 0;
	if (cmd->prev == NULL)
		return (tmp);
	else
	{
		while (cmd->index != i)
		{
			while (tmp->token_status != IS_PIPE)
			{
				tmp = tmp->next;
			}
			tmp = tmp->next;
			i++;
		}
	}
	return (tmp);
}

char	*bootstrap_exp_heredoc(char *buff, t_msc *msc)
{
	char	*str;

	str = ft_strdup(buff);
	free(buff);
	str = ft_strjoin_free("\"", str, str, NULL);
	str = ft_strjoin_free(str, "\"", str, NULL);
	if (ft_strchr(str, '$'))
	{
		str = exp_logic_new(msc, str, NULL);
		ft_shift_to_dollar(str, 1);
	}
	str = kill_quote_heredoc(msc, str);
	str = ft_strjoin_free(str, "\n", str, NULL);
	return (str);
}

char	*kill_quote_heredoc(t_msc *msc, char *str)
{
	char	*buff;
	int		i;
	int		j;

	i = 1;
	j = 0;
	buff = calloc(ft_strlen(str) - 1, sizeof(char));
	if (!buff)
		malloc_error_free_exit(msc, NULL, NULL);
	while (str[i] && i != (int)ft_strlen(str) - 1)
	{
		buff[j] = str[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	free(str);
	return (buff);
}

void	kill_in_out_file(t_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = shift_lex_for_cmd(cmd, cmd->msc->lex);
	while (cmd->full_cmd[i])
	{
		if ((cmd->full_cmd[i][0] == '>' || cmd->full_cmd[i][0] == '<')
			&& tmp->quote_status == 0 && tmp->exp == 0)
		{
			free(cmd->full_cmd[i]);
			cmd->full_cmd[i] = NULL;
			cmd->full_cmd[i] = ft_strdup("");
			free(cmd->full_cmd[i + 1]);
			cmd->full_cmd[i + 1] = NULL;
			cmd->full_cmd[i + 1] = ft_strdup("");
		}
		i++;
		tmp = tmp->next;
	}
	cmd->full_cmd = shorten_arr(cmd->full_cmd, i);
	if (cmd->full_cmd == NULL)
		free_msc_and_exit(cmd->msc, "Memory allocation error: malloc\n");
}
