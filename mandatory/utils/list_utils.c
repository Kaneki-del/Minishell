/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:12:08 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/22 12:44:27 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_lstnew(char *content, t_type_token type, t_gc **g_collector)
{
	t_token	*head;
    static int index;
    
	head = gc(sizeof(t_token), g_collector);
	if (!head)
		return (clear_bin(g_collector), NULL);
	head->value = content;
    head->token_type = type;
    head->index = index;
    index++;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*head;

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
