/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/10 15:10:34 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	print_next(t_dlist **tokens)
{
	t_token	*token;

	if (!(*tokens)->prev)
	{
		token = (*tokens)->content;
		printf("content: %s next: %s\n", token->value,
				((*tokens)->next)->content);
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->next)
	{
		token = (*tokens)->content;
		printf("content: %s next: %s prev: %s\n", token->value,
				((*tokens)->next)->content, ((*tokens)->prev)->content);
		(*tokens) = (*tokens)->next;
	}
}

void	print_prev(t_dlist **tokens)
{
	if (!(*tokens)->next)
	{
		printf("content: %s prev: %s\n", (*tokens)->content,
				((*tokens)->prev)->content);
		(*tokens) = (*tokens)->prev;
	}
	else if ((*tokens)->prev)
	{
		printf("content: %s next: %s prev: %s\n", (*tokens)->content,
				((*tokens)->next)->content, ((*tokens)->prev)->content);
		(*tokens) = (*tokens)->prev;
	}
}

void	print_tokenlist(t_dlist *list)
{
	t_token	*token;

	while (list->next)
	{
		token = list->content;
		printf("token->value: %s type: %d\n", token->value, token->type);
		list = list->next;
	}
}
