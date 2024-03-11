/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:48:39 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/05 22:48:40 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

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

void	print_token(char *msj, t_token	*token)
{
	printf("%s: ", msj);
	printf("token->value: %s type: %d\n", token->value, token->type);
}

void	print_token_args(t_dlist *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = token_list->content;
		if (token->type == CMD)
		{
			printf("token->value: %s type: %d\n", token->value, token->type);
			ft_print_strarray(token->cmds);
		}
		token_list = token_list->next;
	}
}
