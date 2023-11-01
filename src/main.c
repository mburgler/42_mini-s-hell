/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:38:40 by mburgler          #+#    #+#             */
/*   Updated: 2023/10/26 19:54:42 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_status = 0;

t_msc	*init_msc(char **env)
{
	t_msc	*msc;

	msc = malloc(sizeof(t_msc));
	if (!msc)
		return NULL;
	msc->lex = NULL;
	msc->cmd = NULL;
	msc->loop = true;
	msc->input = NULL;
	msc->env_user = getenv("USER");
	msc->env_path = getenv("PATH");
	msc->env_cwd = getcwd(NULL, 0);
	msc->env_home = getenv("HOME");
	msc->env_cpy = ft_dup_arr(env);
	// msc ->prompt_cwd = NULL;
	// msc->prompt = NULL;
	if (!msc->env_cpy)
	{
		write(2, "Memory allocation error: malloc\n", 22);
		free_all(msc);
		exit(1);
	}
	return (msc);
}

void	handle_input(t_msc *msc)
{
	if (ft_strncmp(msc->input, "exit\0", 5) == 0)
	{
		free_all(msc);
		exit(0);
	}
	if (g_sig_status != 131)
	{
		g_sig_status = 0;
		input_lexer(msc);
	}
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
		if (ft_strlen(msc->input) == 0)
			continue ;
		else
			handle_input(msc);
		add_history(msc->input);
		free_structs_and_input(msc);
	}
	free_all(msc);
	return (0);
}
