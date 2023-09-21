/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:21:20 by abektimi          #+#    #+#             */
/*   Updated: 2023/09/21 21:15:57 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//creates and returns a blank node of type t_list
t_list  *ft_lstnew(t_msc *ms)
{
    t_list  *ret;

    ret = malloc(sizeof(t_list));
    if (!ret)
        return (NULL);
    ret->str = NULL;
    ret->next = NULL;
    ret->prev = NULL;
    ret->msc = ms;
    return (ret);
}

//adds a node 'new' to the back of list 'lst'
void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *tmp;

    if (lst && new)
    {
        if (*lst)
        {
            tmp = ft_lstlast(*lst);
            tmp->next = new;
            new->prev = tmp;
        }
        else
        {
            *lst = malloc(sizeof(t_list));
            *lst = new;
        }
    }
}

//returns a pointer to the last node of list 'lst'
t_list  *ft_lstlast(t_list *lst)
{
    if (lst != NULL)
    {
        while (lst->next)
            lst = lst->next;
    }
    return (lst);
}

//frees all nodes of a list 'lst'
void    ft_lstclear(t_list **lst)
{
    t_list  *tmp;

    if (!lst || !(*lst))
        return ;
    while (lst && *lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        *lst = tmp;
    }
}

//creates and initializes a list with the required number of nodes
//returns a pointer to the first node in the list
t_list  *init_lst(t_msc *msc)
{
    t_list  *ret;
    t_list  *tmp;
    int     wordcount;
    int     i;

    i = 1;
    ret = ft_lstnew(msc);
    if(!ret)
        return (NULL);
    while (i < wordcount)
    {
        tmp = ft_lstnew(msc);
        ft_lstadd_back(&ret, tmp);
        if (!tmp)
        {
            ft_lstclear(&ret);
            free(ret);
            return (NULL);
        }
        i++;
    }
    return (ret);
}