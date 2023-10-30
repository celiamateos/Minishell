/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:22:11 by cmateos           #+#    #+#             */
/*   Updated: 2023/10/30 21:22:21 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 # include "../include/minishell.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof (t_token));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
	}
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
		new->prev = temp;
	}
}


