/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
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
				(char *)((*tokens)->next)->content);
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->next)
	{
		token = (*tokens)->content;
		printf("content: %s next: %s prev: %s\n", token->value,
				(char *)((*tokens)->next)->content, (char *)((*tokens)->prev)->content);
		(*tokens) = (*tokens)->next;
	}
}

void	print_prev(t_dlist **tokens)
{
	if (!(*tokens)->next)
	{
		printf("content: %s prev: %s\n", (char *)(*tokens)->content,
				(char *)((*tokens)->prev)->content);
		(*tokens) = (*tokens)->prev;
	}
	else if ((*tokens)->prev)
	{
		printf("content: %s next: %s prev: %s\n", (char *)(*tokens)->content,
				(char *)((*tokens)->next)->content, (char *)((*tokens)->prev)->content);
		(*tokens) = (*tokens)->prev;
	}
}

void	print_tokenlist(t_dlist *list)
{
	t_token	*token;

	while (list)
	{
		token = list->content;
		printf("token->value: %s type: %d\n", token->value, token->type);
		list = list->next;
	}
}

//@brief funcion que recibe una string y la duplica omitiendo las comillas dobles
//return NULL en caso de error
char *remove_quotes(char *old)
{
    char *new;
    size_t   i = 0;
    size_t  j = 0;

    while (old[i])
    {
        if (old[i] == '\"');
            i--;
        i++;
    }
    new = (char *)malloc((i + 1) * sizeof(char));
    if (!new)
        return (NULL);
    new[i] = '\0';
    i = 0;
    while (old[j])
    {
        if (old[j] != '\"')
            new[i] = old[j];
        else
            j++;
        i++;
        j++;
    }
    return (new);
}