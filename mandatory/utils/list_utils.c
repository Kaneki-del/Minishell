/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:12:08 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/15 00:56:45 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_lstnew(char *content, t_type_token type)
{
	t_token	*head;
    static int index;
    
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
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
