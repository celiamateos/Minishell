/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:09:31 by cmateos           #+#    #+#             */
/*   Updated: 2024/03/21 15:15:58 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free_split_mini(char **arraystr, int row)
{
	int	i;

	i = 0;
	if (arraystr[row] == NULL)
	{
		while (i < row)
		{
			free(arraystr[i]);
			i++;
		}
		free(arraystr);
		return (1);
	}
	return (0);
}

static int	ft_countwords_nextquotes(char const *s, int i, int quotes)
{
	i++;
	while (s[i] && s[i] != quotes)
		i++;
	i++;
	return (i);
}

static int	ft_countwords_minishell(char const *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ft_isspace(s[i]) == 1)
			i++;
		while (s[i] && s[i] != '\"' && s[i] != '\'' && ft_isspace(s[i]) == 0)
			i++;
		if (s[i] == '\"')
			i = ft_countwords_nextquotes(s, i, '\"');
		else if (s[i] == '\'')
			i = ft_countwords_nextquotes(s, i, '\'');
		if (s[i] == '\0' || ft_isspace(s[i]) == 1
			|| s[i] == '\"' || s[i] == '\'')
		{
			count++;
			if (s[i] == '\0')
				return (count);
		}
	}
	return (count);
}

//SPLIT_MINISHELL
/*@Brief ALLOCATE MEMORY. split words, but if found quotes, split strings.*/
char	**ft_split_minishell_run(const char *s, char *temp, int wc, int i)
{
	char	**arraystr;
	int		row;

	row = 0;
	arraystr = malloc((wc + 1) * sizeof(char *));
	if (!arraystr)
		return (NULL);
	while (row < wc)
	{
		if (s[i] != '\0' && ft_isspace(temp[i]) == 0)
		{
			arraystr[row] = ft_substr(temp, i, ft_lenstring_minishell(temp, i));
			if (ft_free_split_mini(arraystr, row++) == 1)
				return (free(temp), NULL);
			i += ft_lenstring_minishell(temp, i);
		}
		else
			i++;
	}
	arraystr[row] = NULL;
	return (arraystr);
}

char	**ft_split_minishell(char const *s)
{
	char	**arraystr;
	char	*temp;
	int		i;
	int		wc;

	if (!s)
		return (NULL);
	i = 0;
	temp = ft_strtrim(s, " \t\v\n\r");
	if (!temp)
		return (NULL);
	wc = ft_countwords_minishell(temp);
	arraystr = ft_split_minishell_run(s, temp, wc, i);
	free (temp);
	return (arraystr);
}
