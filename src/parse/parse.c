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

int	check_iscomand(char c)
{
	if (c == '-' || c == '_' || c == '.'
		|| !ft_isalpha(c) || !ft_isalnum(c)
		|| c == D_QUOTES || c == S_QUOTES)
		return (1);
	return (0);
}

int	check_validoper2(char *s, int i)
{
	int	index;

	index = i;
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

int	check_validoper(char *s, int i)
{
	if (ft_strlen(s) < 4)
		return (1);
	if (s[i] == '|')
	{
		if (i < 2 || !s[i + 1] || (!ft_isspace(s[i - 1]) && s[i - 1] != '|')
			|| (!ft_isspace(s[i + 1]) && s[i + 1] != '|'))
			return (2);
	}
	if ((s[i] == '<' || s[i] == '>') && (!s[i + 1]))
		return (2);
	check_validoper2(s, i);
	return (0);
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
		if (s[i] == '|' && str == 1 && check_validoper(s, i))
			return (put_syntaxerror('|'), 2);
		if (s[i] == '<' && str == 1 && check_validoper(s, i))
			return (put_syntaxerror('<'), 2);
		if (s[i] == '>' && str == 1 && check_validoper(s, i))
			return (put_syntaxerror('>'), 2);
	}
	return (0);
}

int	check_errors_initsack(t_shell_sack **sack)
{
	char	*s;
	int		d_quotes;
	int		s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	s = (*sack)->line;
	if (!s || s[0] == '\0')
		return (1);
	if (check_open_quotes(s, d_quotes, s_quotes))
		return (ft_putstr_fd("Input invalid, found open quotes\n", 2), 2);
	if (check_emptyorspace((*sack)->line))
		return (1);
	if (check_syntaxerrors(&sack, s))
	{
		(*sack)->last_exit = 2;
		return (1);
	}
	if (check_open_parentheses(s))
		return (ft_putstr_fd("Input invalid, "
				"parentheses doesn't match\n", 2), 2);
	return (0);
}
