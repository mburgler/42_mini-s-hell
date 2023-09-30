/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:38:40 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/29 17:23:19 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_status = 0;

void	init_msc(t_msc *msc, char **env)
{
	msc->loop = true;
	msc->input = NULL;
	msc->env_cpy = ft_dup_arr(env);
	msc->lex = NULL;
	msc->env_cwd = getcwd(NULL, 0);
	msc->env_home = getenv("HOME");
	// msc ->prompt_cwd = NULL;
	// msc->prompt = NULL;
	if(!msc->env_cpy)
	{
		write(2, "Error: malloc failed\n", 22);
		free_all(msc);
		exit(1);
	}
	msc->env_path = getenv("PATH");
	msc->env_user = getenv("USER");
	//set_prompt_and_cwd(msc);
	msc->env_cpy = ft_dup_arr(env);
	if(msc->env_cpy == NULL)
	{
		write(2, "Error: malloc failed\n", 22);
		free_all(msc);
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_msc *msc;

	if (argc != 1 || !argv[0] || !env)
		return (-1);
	msc = ft_calloc(1, sizeof(t_msc));
	if (!msc)
		return (-1);
	init_msc(msc, env);
	while(msc->loop == true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		msc->input = readline("minishell $ ");
        if (!msc->input) 
		{
            printf("\n");
            break;
        }
        if (ft_strncmp(msc->input, "exit\0", 5) == 0) 
		{
            free(msc->input);
            break;
        }
		if(g_sig_status != 131)
		{
        	//printf("You entered: %s\n\n", msc->input);
			input_lexer(msc);
			g_sig_status = 0;
		}
		add_history(msc->input);
		free(msc->input);
		//set_prompt_and_cwd(msc);
	}
	

	
	// if (parsing(argc, argv, msc) == -1)
	// 	return (free_all(msc), -1);
	// debug_print_list(msc->list);
	free_all(msc);
	return (0);
}