/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:07:18 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:14:35 by daviles-         ###   ########.fr       */
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

int	ft_isoperator(char	c, int *quotes)
{
	if (c == '"')
		quotes[0] = !quotes[0];
	else if (c == '\'')
		quotes[1] = !quotes[1];
	if (quotes[0] || quotes[1])
		return (0);
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '&')
		return (1);
	return (0);
}

void	*get_next_token(char *line, int *i)
{
	t_token	*token;
	int		start;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	start = *i;
	if (ft_isoperator(line[*i], quotes))
		while (ft_isoperator(line[*i], quotes) && line[*i])
			*i = *i + 1;
	else
		while (!ft_isoperator(line[*i], quotes) && line[*i])
			*i = *i + 1;
	token = malloc(sizeof(t_token));
	token->value = ft_substr(line, start, (size_t)(*i - start));
	token->type = get_token_type(token->value);
	return ((void *)token);
}

t_dlist	*init_tokens(char *line)
{
	int		i;
	t_dlist	*list;

	i = 0;
	list = ft_dlstnew(get_next_token(line, &i));
	while (line[i])
		ft_dlstadd_back(&list, ft_dlstnew(get_next_token(line, &i)));
	return (list);
}

t_dlist	*lexer(char *line)
{
	t_dlist	*list;

	list = init_tokens(line);
//	print_tokenlist(list);
	return (list);
}
