/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:57:56 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/15 10:18:48 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data *new_data_node(char **command, char **directions)
{
    t_data *head;
    head = malloc(sizeof(t_data));
    if (!head)
        return (NULL);
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