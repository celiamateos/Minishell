/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:36:23 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/21 12:36:25 by cmateos-         ###   ########.fr       */
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
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] == '\0' || ft_isspace(s[i]) == 1 || s[i] == '\"' || s[i] == '\'')
		{
			count++;
			if (s[i] == '\0')
				return (count);
		}
	}
	return (count);
}


static int	ft_lenstring_minishell(char const *s, int i)
{
	int	start;

	if (!s)
		return (0);
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '\0')
		return (0);
	start = i;
	while (s[i])
	{
		while (s[i] && s[i] != '\"' && s[i] != '\'' && ft_isspace(s[i]) == 0)
			i++;
		if (s[i] == '\0' || ft_isspace(s[i]) == 1)
			return (i - start);
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			i++;
			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '\"' && s[i] != '\'')
				i++;
			return (i - start);
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '\"' && s[i] != '\'')
				i++;
			return (i - start);
		}
		i++;
	}
	return (0);
}



// static int	ft_lenstring_minishell(char const *s, int i)
// {
// 	int	start;

// 	if (!s)
// 		return (0);
// 	while (s[i] && ft_isspace(s[i]) == 1)
// 		i++;
// 	if (s[i] == '\0')
// 		return (0);
// 	start = i;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] != '\"' && s[i] != '\'' && ft_isspace(s[i]) == 0)
// 			i++;
// 		if (s[i] == '\0')
// 			return (i - start);
// 		if (ft_isspace(s[i]) == 1)
// 			return (i - start);
// 		if (s[i] == '\"')
// 		{
// 			i++;
// 			while (s[i] && s[i] != '\"')
// 				i++;
// 			i++;
// 			while (s[i] && ft_isspace(s[i]) == 0)
// 				i++;
// 			return (i - start);
// 		}
// 		if (s[i] == '\'')
// 		{
// 			i++;
// 			while (s[i] && s[i] != '\'')
// 				i++;
// 			i++;
// 			while (s[i] && ft_isspace(s[i]) == 0)
// 				i++;
// 			return (i - start);
// 		}
// 		i++;
// 	}
// 	return (0);
// }


//SPLIT_MINISHELL
/*@Brief ALOCA MEMORIA pensado para hacer un split por palabras excepto
si encuentra comillas que entonces tomara ese tramo como una 'palabra'
el tokenizador de palabras por espacios da mucos problemas en distintas 
partes del codigo, entiendo que bash tokeniza de esta manera*/
char	**ft_split_minishell(char const *s)
{
	char	**arraystr;
	int		i;
	int		row;
	int		wc;

	if (!s)
		return (NULL);
	i = 0;
	row = 0;
	wc = ft_countwords_minishell(s);
	// printf("countwords:%d\n", wc);
	arraystr = malloc((wc + 1) * sizeof(char *));
	if (!arraystr)
		return (NULL);
	while (row < wc)
	{
		if (s[i] != '\0' && ft_isspace(s[i]) == 0)
		{
			arraystr[row] = ft_substr(s, i, ft_lenstring_minishell(s, i));
			// printf("arraystr[%d]:%s      len:%d\n", row, arraystr[row], ft_lenstring_minishell(s, i));
			if (ft_free_split_mini(arraystr, row++) == 1)
				return (NULL);
			i += ft_lenstring_minishell(s, i);
		}
		else
			i++;
	}
	arraystr[row] = NULL;
	return (arraystr);
}

// int	main()
// {
// 	char *s = "echo hola que tal";
// 	// char *s = "hola que tal ";
// 	ft_split_minishell(s);
// 	return(0);
// }
