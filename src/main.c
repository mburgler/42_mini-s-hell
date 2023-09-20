/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:38:40 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/20 16:19:42 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_msc *msc;
	char	*input;
	if (argc != 1 || !argv[0] || !env)
		return (-1);
	msc = ft_calloc(1, sizeof(t_msc));
	if (!msc)
		return (-1);
	msc->loop = true;
	while(msc->loop == true)
	{
		input = readline("MyShell> "); // Display a prompt and read user input

        if (!input) {
            // If input is NULL (e.g., user pressed Ctrl+D), exit the loop
            printf("\n");
            break;
        }

        if (ft_strncmp(input, "exit", 4) == 0) {
            // If user enters "exit", exit the shell
            free(input);
            break;
        }

        // Process the user command here
        printf("You entered: %s\n", input);

		add_history(input);
		free(input);
	}
	

	
	// if (parsing(argc, argv, msc) == -1)
	// 	return (free_all(msc), -1);
	// debug_print_list(msc->list);
	return (0);
}