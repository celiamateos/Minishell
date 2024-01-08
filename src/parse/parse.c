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
#include"../../include/minishell.h"
void	put_syntaxerror(char *cmd)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", 2);
}

int	check_isoperator(char c)
{
	if (c == '|' || c == '<'  || c == '>' 
	|| c == '&'  || c == '<'  || c == ')')
		return (1);
	return (0);
}

int	check_validpipe(char *s, int i)
{
	int index = i;

	if (ft_strlen(s) < 4)
		return (1);
	if (i == 0 || !s[i + 1] || !ft_isspace(s[i - 1]) || !ft_isspace(s[i + 1]))
		return (1);
	while (i-- >= 0)
	{
		if (s[i] == '-' || s[i] == '_' || s[i] == '.'
		|| !ft_isalpha(s[i]) || !ft_isalnum(s[i])
		|| s[i] == D_QUOTES || s[i] == S_QUOTES)
			return (0);
		if (check_isoperator(s[i]))
			return (1);
	}
	return (0);
}	

int	check_syntaxerrors(t_shell_sack *sack, char *s)
{
	int i;
	int	str = 1;

	i = -1;
	while (s[++i])
	{
		if (s[i] == S_QUOTES || s[i] == D_QUOTES)
			str = !str;
		if (s[i] == '|' && str == 1)
			if (check_validpipe(s, i))
				return (ft_putstr_fd("minishell: syntax error near unexpected token\n", 2), 1);
	}
	return (0);
}

int check_errors_initsack(t_shell_sack *sack)
{
	char *s;

	s = sack->line;
	if (check_open_quotes(sack, s))
		return (ft_putstr_fd("Input invalid, found open quotes\n", 2), 1);
	if (check_emptyorspace(sack->line))
		return (1);
	if (check_syntaxerrors(sack, s))
		return (1);
	return (0);
}