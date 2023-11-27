/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:38:40 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/27 20:19:05 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_status = 0;

t_msc	*init_msc(char **env)
{
	t_msc	*msc;

	msc = malloc(sizeof(t_msc));
	if (!msc)
		return (NULL);
	msc->lex = NULL;
	msc->cmd = NULL;
	msc->loop = true;
	msc->input = NULL;
	msc->stop_file_error = 0;
	msc->str_file_error = NULL;
	dup_env_head(msc, env);
	msc->env_home = getenv("HOME");
	return (msc);
}

void	handle_input(t_msc *msc)
{
	if (ft_strcmp(msc->input, "exit") == 0)
	{
		free_all(msc);
		exit(0);
	}
	if (g_sig_status != 131)
	{
		input_lexer(msc);
	}
}

int	no_chars(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (!isws(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_msc	*msc;

	if (argc != 1 || !argv[0] || !env)
		return (1);
	msc = init_msc(env);
	if (!msc)
		return (1);
	while (msc->loop == true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		msc->input = readline("minishell $ ");
		if (msc->input == NULL)
			free_msc_and_exit_success(msc);
		else if (ft_strlen(msc->input) == 0 || no_chars(msc->input))
			continue ;
		else
			handle_input(msc);
		add_history(msc->input);
		main_free(msc);
	}
	free_all(msc);
	return (0);
}

//BELOW JUST FOR TESTING PURPOSES - ONLY FOR TESTING; DELETE FROM FINAL VERSION
void	ft_print2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}
