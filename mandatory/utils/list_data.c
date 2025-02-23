/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:57:56 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/23 11:31:50 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data *new_data_node(char **command, char **directions, t_gc **g_collector)
{
    t_data *head;
    head = gc(sizeof(t_data), g_collector);
    if (!head)
        return (clear_bin(g_collector), NULL);
    head->cmds = command;
    head->directions = directions;
    head->next = NULL;
    return (head);
}

void add_data_back(t_data **lst, t_data *new)
{
    t_data *current;

    if (!lst || !new)
        return;
    if (*lst)
    {
        current = *lst;
        while (current->next)
            current = current->next;
        current->next = new;
    }
    else
        *lst = new;
}