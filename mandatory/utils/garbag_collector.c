/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbag_collector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:36:44 by kben-tou          #+#    #+#             */
/*   Updated: 2025/03/22 21:40:32 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_gc	*gc_node(t_gc **garbage_list)
{
	t_gc	*last_node;

	if (!garbage_list)
		return (NULL);
	last_node = *garbage_list;
	if (last_node == NULL)
		return (*garbage_list = ft_calloc(sizeof(char), sizeof(t_gc)));
	while (last_node && last_node->next)
		last_node = last_node->next;
	return (last_node->next = ft_calloc(sizeof(char), sizeof(t_gc)));
}

void	clear_bin(t_gc **garbage_list)
{
	t_gc	*current;
	t_gc	*next;

	if (!garbage_list)
		return ;
	current = *garbage_list;
	next = NULL;
	while (current)
	{
		next = current->next;
		free(current->adress);
		free(current);
		current = NULL;
		current = next;
	}
	garbage_list = NULL;
}

void	*gc(size_t size, t_gc **garbage_list, t_container *content)
{
	t_gc	*new_garbage_node;
	void	*allocated;

	new_garbage_node = NULL;
	allocated = ft_calloc(sizeof(char), size);
	if (allocated == NULL)
	{
		write(2, "allocation failed!", 17);
		clean_exit2(content, 1);
	}
	new_garbage_node = gc_node(garbage_list);
	if (new_garbage_node == NULL)
	{
		write(2, "allocation failed!", 17);
		clean_exit2(content, 1);
	}
	new_garbage_node->adress = allocated;
	new_garbage_node->next = NULL;
	return (allocated);
}
