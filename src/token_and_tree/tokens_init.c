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
#include "../../include/minishell.h"

void	ft_whileoperator(char *line, int *quotes, int *i)
{
	while (ft_isoperator(line[*i], quotes) && line[*i])
	{
		if (line[*i] == '<' || line[*i] == '>')
		{
			save_redir_filename(line, i);
			break ;
		}
		else
			*i = *i + 1;
	}
}

int	ft_isoperator(char c, int *quotes)
{
	if (c == '\"' && !quotes[1])
		quotes[0] = !quotes[0];
	else if (c == '\'' && !quotes[0])
		quotes[1] = !quotes[1];
	if (quotes[0] || quotes[1])
		return (0);
	if (c == '|' || c == '<' || c == '>' || c == ';'
		|| c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

t_token	*create_token(char *aux)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = get_token_type(aux);
	token->value = fix_tokenvalues(&aux);
	token->oper = 0;
	return (token);
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
		ft_whileoperator(line, quotes, i);
	else
	{
		*i = *i + 1;
		while (!ft_isoperator(line[*i], quotes) && line[*i])
			*i = *i + 1;
	}
	aux = ft_substr(line, start, (size_t)(*i - start));
	if (aux && !check_emptyorspace(aux))
	{
		token = create_token(aux);
		return ((void *)token);
	}
	else
		free(aux);
	return (NULL);
}

t_dlist	*init_tokens(char *line, t_shell_sack **sack)
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
	if (validate_tokens(list, &sack))
	{
		ft_dlstclear(&list, &free_token_noargs);
		return (NULL);
	}
	return (list);
}
