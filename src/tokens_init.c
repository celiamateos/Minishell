/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:07:18 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/21 21:59:42 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	get_token_type(char *value)
{
	int	i;

	i = 0;
	if (!ft_strncmp(value, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(value, "<<", 2))
	{
		i = 2;
		if (valid_filename(value, i))
			return (HEREDOC);	
		else
			return (FN_ERROR); //Deberiamos retornar error? Filename error
	}
	else if (value[i] == '<')
	{
		i = 1;
		if (valid_filename(value, i))
			return (REDIR_IN);	
		else
			return (FN_ERROR); 
	}
	else if (!ft_strncmp(value, ">>", 2))
	{
		i = 2;
		if (valid_filename(value, i))
			return (APPEND_OUT);	
		else
			return (FN_ERROR); 
	}
	else if (value[i] == '>')
	{
		i = 1;
		if (valid_filename(value, i))
			return (REDIR_OUT);	
		else
			return (FN_ERROR); 
	}
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
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	start = *i;
	if (ft_isoperator(line[*i], quotes))
		while (ft_isoperator(line[*i], quotes) && line[*i])
		{
			 if (line[*i] == '<' || line[*i] == '>' )
			 	save_redir_filename(line, i);
			else
				*i = *i + 1;
		}
	else
		while (!ft_isoperator(line[*i], quotes) && line[*i])
			*i = *i + 1;
	aux = ft_substr(line, start, (size_t)(*i - start));
	if (aux && !check_emptyorspace(aux))
	{
		token = malloc(sizeof(t_token));
		token->value = aux;
		token->type = get_token_type(token->value);
		return ((void *)token);
	}
	return (NULL);
}

t_dlist	*init_tokens(char *line)
{
	int		i;
	t_dlist	*list;
	t_token	*token;

	i = 0;
	token = get_next_token(line, &i);
	if (token != NULL)
		list = ft_dlstnew(token);
	while (line[i])
	{
		token = get_next_token(line, &i);
		if (token != NULL)
			ft_dlstadd_back(&list, ft_dlstnew(token));
	}
	return (list);
}

t_dlist	*lexer(char *line)
{
	t_dlist	*list;

	list = init_tokens(line);
//	print_tokenlist(list);
	return (list);
}
