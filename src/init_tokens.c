/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:07:18 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/10 14:13:14 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	get_token_type(char *value)
{
	if (!ft_strncmp(value, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(value, "<", 2) || !ft_strncmp(value, "<<", 3) \
			|| !ft_strncmp(value, ">", 2) || !ft_strncmp(value, ">>", 3))
		return (REDIR);
	else if (!ft_strncmp(value, "&&", 3) || !ft_strncmp(value, "||", 3))
		return (OPER);
	else
		return (CMD);
}

int	ft_isoperator(char	c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&')
		return (1);
	return (0);
}

void	*get_next_token(char *line, int *i)
{
	t_token	*token;
	int		start;

//	while (line[*i])
//	{
		start = *i;
		if (ft_isoperator(line[*i]))
			while (ft_isoperator(line[*i]) && line[*i])
				*i = *i + 1;
		else
			while (!ft_isoperator(line[*i]) && line[*i])
				*i = *i + 1;
		token = malloc(sizeof(t_token));
		token->value = ft_substr(line, start, (size_t)(*i - start));
		token->type = get_token_type(token->value);
//		printf("token->value: %s type: %d\n", token->value, token->type);
//	}
	return ((void *)token);
}

void	init_tokens(t_dlist *list, char *line)
{
	t_dlist	*temp;
	t_dlist	*last;
	int		i;
	t_token	*token;

	i = 0;
	last = NULL;
	temp = list;
	while (line[i])
	{
		last = temp;
		temp = ft_dlstnew(get_next_token(line, &i));
		token = temp->content;
		printf("token->value: %s type: %d\n", token->value, token->type);
		ft_dlstadd_back(&list, temp);
		temp = temp->next;
	}
	if (last)
	{
		last->next = NULL;
	}
/*	while (list->next)
	{
		token = list->content;
		printf("token->value: %s type: %d\n", token->value, token->type);
		list = list->next;
	}
	
	while ((temp)->next)
	{
		print_next(&temp);
		temp = (temp)->next;
	}
*/
}

t_dlist	*lexer(char *line)
{
	t_dlist	*list;

	list = ft_dlstnew(NULL);
	init_tokens(list, line);
/*	while (list->next)
	{
		print_next(&list);
		list = list->next;
	}
*/
	//printf("HOLA");
	return (list);
}
