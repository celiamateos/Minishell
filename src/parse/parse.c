/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:53:46 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/09 03:47:00 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// int check_errors_opers(t_dlist *list)
// {
// 	t_token	*token;
// 	int		type;

// 	token = list->content;
// 	type = token->type;
// 	if (type > 0 && list == NULL)
// 		return (1);
// 	list = list->next;
// 	while (list)
// 	{
// 		token = list->content;
// 		if (type != 0)
// 			if (token->type != 0)
// 				return (1);
// 		// printf("token->value: %s type: %d\n", token->value, token->type);
// 		type = token->type;
// 		list = list->next;
// 	}
// 	return (0);
// }
///

void	put_syntaxerror(int cmd)
{
	if (cmd == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token: '|'\n", 2);
	if (cmd == '<')
		ft_putstr_fd("minishell: syntax error near unexpected token: '<'\n", 2);
	if (cmd == '>')
		ft_putstr_fd("minishell: syntax error near unexpected token: '>'\n", 2);
}

int	check_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ')')
		return (1);
	return (0);
}

int	check_iscomand(char c)
{
	if (c == '-' || c == '_' || c == '.'
		|| !ft_isalpha(c) || !ft_isalnum(c)
		|| c == D_QUOTES || c == S_QUOTES)
		return (1);
	return (0);
}

// int check_valid_heredoc(char *s, int i)
// {
// 	i++;
// 	if (s[i] + 1)
// 	while (s[i])
// }

int	check_validoper(char *s, int i)
{
	int	index;

	index = i;
	if (ft_strlen(s) < 4)
		return (1);
	if (s[i] == '|')
	{
		if (i < 2 || !s[i + 1] || (!ft_isspace(s[i - 1]) && s[i - 1] != '|')
			|| (!ft_isspace(s[i + 1]) && s[i + 1] != '|'))
			return (2);
	}
	if (s[i] == '<' || s[i] == '>')
	{
		if (!s[i + 1])
			return (2);
		// if (s[i] == '<' && s[i + 1] == '<')
		// {
		// 	if (check_valid_heredoc(s, i) == 1)
		// 		return (2);
		// }
	}
	while (i >= 0)
	{
		if (ft_isspace(s[i]) == 1)
			i--;
		else if (check_iscomand(s[i]))
			return (0);
		else if (check_isoperator(s[i]))
			return (2);
		i--;
	}                                         
	while (s[index++])
	{
		if (ft_isspace(s[i]))
			index++;
		else if (check_iscomand(s[i]))
			return (0);
		else if (check_isoperator(s[i]))
			return (2);
	}
	return (2);
}

int	check_syntaxerrors(t_shell_sack ***sack, char *s)
{
	int	i;
	int	str;

	str = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] == S_QUOTES || s[i] == D_QUOTES)
			str = !str;
		if (s[i] == '|' && str == 1)
		{
			if (check_validoper(s, i))
			{
				(**sack)->last_exit = 2;
				return (put_syntaxerror('|'), 2);
			}
		}
		if (s[i] == '<' && str == 1)
		{
			if (check_validoper(s, i))
			{
				(**sack)->last_exit = 2;
				return (put_syntaxerror('<'), 2);
			}
		}
		if (s[i] == '>' && str == 1)
		{
			if (check_validoper(s, i))
			{
				(**sack)->last_exit = 2;
				return (put_syntaxerror('>'), 2);
			}
		}
		
		// if (s[i] == ')' && str == 1) arreglar esto pa k no de segfault con )
		// {
		// 	if (check_validoper(s, i))
		// 	{
		// 		sack->last_exit = 2;
		// 		return (put_syntaxerror(')'), 2);
		// 	}
		// }
	}
	return (0);
}

int check_errors_initsack(t_shell_sack **sack)
{
	char	*s;

	s = (*sack)->line;
	if (check_open_quotes(s))
		return (ft_putstr_fd("Input invalid, found open quotes\n", 2), 2);
	if (check_emptyorspace((*sack)->line))
		return (1);
	if (check_syntaxerrors(&sack, s))
		return (1);
	if (check_open_parentheses(s))
		return (ft_putstr_fd("Input invalid, parentheses doesn't match\n", 2), 2);
	return (0);
}
