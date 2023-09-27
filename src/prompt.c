/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:20:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/27 23:24:29 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void set_custom_cwd(t_msc *msc)
{
    char *cwd;
	char *pos;

    cwd = getcwd(NULL, 0);
    if (msc->env_home && cwd)
    {
        pos = ft_strnstr(cwd, msc->env_home, \
			ft_strlen(msc->env_home));
        if (pos)
        {
			msc->prompt_cwd = ft_strjoin("~", pos + ft_strlen(msc->env_home));
            free(cwd);
            return ;
        }
		free(cwd);
    }
    else if (!msc->env_home && cwd)
    {
        msc->prompt_cwd = cwd;
		free(cwd);
        return ;
    }
    else
        msc->prompt_cwd = "";
}

void	set_prompt_and_cwd(t_msc *msc)
{
	char 	*tmp;
	char	*tmp2;

	msc->env_cwd = getcwd(NULL, 0);
	if(msc->env_user == NULL)
		msc->env_user = "guest";
	tmp = ft_strjoin(msc->env_user, "@minishell ");
	if(!tmp)
	{
		write(2, "Error: malloc failed\n", 22);
		free_all(msc);
		exit(1);
	}
	set_custom_cwd(msc);
	tmp2 = ft_strjoin(tmp, msc->prompt_cwd);
	free(tmp);
	if(!tmp2)
	{
		write(2, "Error: malloc failed\n", 22);
		free_all(msc);
		exit(1);
	}
	msc->prompt = ft_strjoin(tmp2, " $ ");
	free(tmp2);
}
