/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:38:25 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/07 23:38:28 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	goto_nextquote(char *s, int i)
{
	if (s[i] == D_QUOTES)
	{
		while (s[++i] != D_QUOTES && s[i])
			if (s[i] == D_QUOTES)
				break ;
	}
	else if (s[i] == S_QUOTES)
	{
		while (s[++i] != S_QUOTES && s[i])
			if (s[i] == S_QUOTES)
				break ;
	}
	return (i);
}

// @brief revise if open parentheses or invalid use of them
int	check_open_parentheses(char *s)
{
	int	i;
	int	par_op;
	int	par_cl;

	par_op = 0;
	par_cl = 0;
	i = -1;
	if (!s || s[i + 1] == '\0')
		return (1);
	while (s[++i])
	{
		if (s[i] == D_QUOTES || s[i] == S_QUOTES)
			i = goto_nextquote(s, i);
		else if (s[i] == PAR_O)
			par_op++;
		else if (s[i] == PAR_C)
		{
			if (!par_op)
				return (1);
			par_cl++;
		}
	}
	if (par_op != par_cl)
		return (1);
	return (0);
}

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

// @brief revise if open quotes string
// @param s string to revise 
// @return 1 if open quotes
int	check_open_quotes(char *s, int d_quotes, int s_quotes)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == D_QUOTES)
		{
			d_quotes = !d_quotes;
			if (!search_char(s, D_QUOTES, i + 1))
				break ;
			i = search_char(s, D_QUOTES, i + 1);
			d_quotes = !d_quotes;
		}
		else if (s[i] == S_QUOTES)
		{
			s_quotes = !s_quotes;
			if (!search_char(s, S_QUOTES, i + 1))
				break ;
			i = search_char(s, S_QUOTES, i + 1);
			s_quotes = !s_quotes;
		}
	}
	if (d_quotes != 0 || s_quotes != 0)
		return (1);
	return (0);
}
