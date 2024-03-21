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


// static int	ft_lenstring_minishell(char const *s, int i)
// {
// 	int	start;

// 	if (!s)
// 		return (0);
// 	while (s[i] && ft_isspace(s[i]) == 1)
// 		i++;
// 	if (s[i] == '\0')
// 		return (-1);
// 	start = i;
// 	printf("\ns:%s", s);
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] != '\"' && s[i] != '\'' && ft_isspace(s[i]) == 0)
// 			i++;
// 		if (s[i] == '\0' || ft_isspace(s[i]) == 1)
// 			return (i - start);
// 		if (s[i] == '\"')
// 		{
// 			i++;
// 			while (s[i] && s[i] != '\"')
// 				i++;
// 			i++;
// 			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '\"' && s[i] != '\'')			
// 				i++;
// 			printf("\npos:%d", (i - start));
// 			return (i - start);
// 		}
// 		if (s[i] == '\'')
// 		{
// 			i++;
// 			while (s[i] && s[i] != '\'')
// 				i++;
// 			i++;
// 			while (s[i] && ft_isspace(s[i]) == 0 && s[i] != '\"' && s[i] != '\'')
// 				i++;
// 			return (i - start);
// 		}
// 		i++;
// 	}
// 	return (0);
// }


static int	ft_lenstring_minishell(char const *s, int i)
{
	int	start;

	if (!s)
		return (0);
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '\0')
		return (-1);
	start = i;
	// printf("\ns:%s", s);
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
			while (s[i] && ft_isspace(s[i]) == 0)		
				i++;
			// printf("\npos:%d", (i - start));
			return (i - start);
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
			while (s[i] && ft_isspace(s[i]) == 0)
				i++;
			return (i - start);
		}
		i++;
	}
	return (0);
}

//SPLIT_MINISHELL
/*@Brief ALOCA MEMORIA pensado para hacer un split por palabras excepto
si encuentra comillas que entonces tomara ese tramo como una 'palabra'
el tokenizador de palabras por espacios da mucos problemas en distintas 
partes del codigo, entiendo que bash tokeniza de esta manera*/
char	**ft_split_minishell(char const *s)
{
	char	**arraystr;
	char 	*temp;
	int		i;
	int		row;
	int		wc;

	if (!s)
		return (NULL);
	i = 0;
	row = 0;
	temp = ft_strtrim(s, " \t\v\n\r");
	if (!temp)
		return (NULL);
	wc = ft_countwords_minishell(temp);
	// printf("\ncountwords:%d\n", wc);
	// printf("s:%s.", s); //CON UN STRITRIM AKI SE SOLUCIONA :)
	// printf("temp:%s.", temp); //CON UN STRITRIM AKI SE SOLUCIONA :)
	arraystr = malloc((wc + 1) * sizeof(char *));
	if (!arraystr)
		return (NULL);
	while (row < wc)
	{
		if (s[i] != '\0' && ft_isspace(temp[i]) == 0)
		{
			arraystr[row] = ft_substr(temp, i, ft_lenstring_minishell(temp, i));
			// printf("\narraystr[%d]:%s\nlen:%d\n", row, arraystr[row], ft_lenstring_minishell(temp, i));
			if (ft_free_split_mini(arraystr, row++) == 1)
				return (free(temp), NULL);
			i += ft_lenstring_minishell(temp, i);
		}
		else
		i++;
	}
	arraystr[row] = NULL;
	free (temp);
	return (arraystr);
}

// int main()
// {
// 	char *s = "echo \"hola\" que \"tal\"";
// 	ft_split_minishell(s);
// 	return 0;
// }


