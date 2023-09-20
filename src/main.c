/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:38:40 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/20 19:37:19 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_prompt(t_msc *msc)
{
	char	*user;

	user = msc->env_user;
	if(!user)
		user = "guest";
	msc->prompt = ft_strjoin(user, "@minishell $ ");
}

void	init_msc(t_msc *msc, char **env)
{
	msc->loop = true;
	msc->input = NULL;
	msc->env_path = getenv("PATH");
	msc->env_user = getenv("USER");
	set_prompt(msc);
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
		msc->input = readline(msc->prompt); // Display a prompt and read user input

        if (!msc->input) 
		{
            // If input is NULL (e.g., user pressed Ctrl+D), exit the loop
            printf("\n");
            break;
        }

        if (ft_strncmp(msc->input, "exit\0", 5) == 0) 
		{
            // If user enters "exit", exit the shell
            free(msc->input);
            break;
        }

        // Process the user command here
        printf("You entered: %s\n", msc->input);

		add_history(msc->input);
		free(msc->input);
	}
	

	
	// if (parsing(argc, argv, msc) == -1)
	// 	return (free_all(msc), -1);
	// debug_print_list(msc->list);
	free_all(msc);
	return (0);
}