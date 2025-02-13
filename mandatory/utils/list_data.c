/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:57:56 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/13 16:21:56 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data *new_data_node(char **command, char **directions, t_type_token dir_input_type, t_type_token dir_output_type)
{
    t_data *head;
    head = malloc(sizeof(t_data));
    if (!head)
        return (NULL);
    head->cmds = command;
    head->directions = directions;
    head->dir_input_type = dir_input_type;
    head->dir_output_type = dir_output_type;
    head->next = NULL;
    return (head);
}

void	add_data_back(t_data **lst, t_data *new)
{
	t_data	*head;

	if (!lst || !new)
		return ;
	if (*lst != NULL)
	{
		head = *lst;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	else
		*lst = new;
}