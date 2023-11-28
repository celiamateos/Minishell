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

int	check_emptyorspace(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (!str || str == NULL)
		return (1);	
	while (str[i])
	{
		if (isspace(str[i]))
			space++;
		i++;
	}
	if (i == space)
		return (1);
	return (0);
}

int	find_nextquote(char *str, char quote)
{
	int	i;
	int	closed;

	i = 0;
	closed = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
		{
			closed = 1;
			break;
		}
		i++;
	}
	if (closed)
		return (i);
	else
		return (-1);
}

int	valid_filename(char *value, int i)
{
	if (ft_isspace(value[i]))
		while (ft_isspace(value[i]))
			i++;
	if (!ft_isalnum(value[i]))
		return (0); //Deberiamos retornar error?
	else
		i++;
	while (value[i] != '\0')
	{
		if (ft_isalnum(value[i]) || value[i] == '.' || value[i] == '_' || value[i] == '-')
			i++;
		else if (ft_isspace(value[i]))
			break;
		else
			return (0); //Deberiamos retornar error?
	}
		return (1);
}

void	save_redir_filename(char *line, int *i)
{
	*i = *i + 1;
	if (line[*i] == '<' || line[*i] == '>')
		*i = *i + 1;
	if (ft_isspace(line[*i]))
	{
		while (ft_isspace(line[*i]) && line[*i] != '\0')
			*i = *i + 1;
	}
	while (ft_isalnum(line[*i]) || line[*i] == '.' || line[*i] == '_' || line[*i] == '-')
	{
			*i = *i + 1;
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

void	print_token(char *msj, t_token	*token)
{
	printf("%s: ", msj);
	printf("token->value: %s type: %d\n", token->value, token->type);
}