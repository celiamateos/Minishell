/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:03:58 by cmateos           #+#    #+#             */
/*   Updated: 2024/04/04 19:04:00 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_lenstr_while_quotes(char const *s, int i, int start, int quotes)
{
	i++;
	while (s[i] && s[i] != quotes)
		i++;
	i++;
	while (s[i] && ft_isspace(s[i]) == 0)
		i++;
	return (i - start);
}

static int	ft_lenstring_minishell_while(char const *s, int i, int start)
{
	while (s[i])
	{
		while (s[i] && s[i] != '\"' && s[i] != '\'' && ft_isspace(s[i]) == 0)
			i++;
		if (s[i] == '\0' || ft_isspace(s[i]) == 1)
			return (i - start);
		if (s[i] == '\"')
			return (ft_lenstr_while_quotes(s, i, start, '\"'));
		if (s[i] == '\'')
		{
			return (ft_lenstr_while_quotes(s, i, start, '\''));
		}
		i++;
	}
	return (0);
}

int	ft_lenstring_minishell(char const *s, int i)
{
	int	start;

	if (!s)
		return (0);
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '\0')
		return (-1);
	start = i;
	return (ft_lenstring_minishell_while(s, i, start));
	return (0);
}
