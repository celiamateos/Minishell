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
#include"../../include/minishell.h"
 








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
int check_open_parentheses(char *s)
{
	int i;
	int	par_op = 0;
	int	par_cl = 0;
	
	i = -1;
	if (!s || s[i + 1] == '\0')
		return (1); //No se si hay que proteger aqui.
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

// @brief revise if open quotes string
// @param s string to revise 
// @return 1 if open quotes
int check_open_quotes(char *s)
{
	int i;
	int	d_quotes = 0;
	int	s_quotes = 0;
	
	i = -1;
	if (!s || s[i + 1] == '\0')
		return (1); //No se si hay que proteger aqui.
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

// //NO SE USA PERO VAYA JEJE
// /*@brief ALOCA MEMORIA.
// Recibe una string y aloca memoria para una copia
// en la que elimina una parte de la string
// @param start inicio de la parte a eliminar
// @param lenn final de la parte a eliminar*/
// char *remove_partofstr(const char *s, size_t start, size_t len)
// {
//     // size_t	original_len;
// 	size_t	i;
// 	size_t	j;
// 	char*	new;

// 	i = 0;
// 	j = 0;
//     if (!s || !len)
//         return (NULL);
// 	// original_len = ft_strlen(s);
//     if (start >= ft_strlen(s) || (start + len) > ft_strlen(s))
//         return (NULL);
//     new = (char *)malloc((ft_strlen(s) - len + 1) * sizeof(char));
//     if (!new)
//         return NULL;
//     while (s[i] != '\0')
//     {
//         if (i >= start && i < (start + len))
//             i++;
//         else
//             new[j++] = s[i++];
//     }
//     new[j] = '\0';
//     return new;
// }

// // @brief NO SE USA
// int	check_emptystr(char *line, size_t i)
// {
//     if (!line || i > ft_strlen(line))
//         return (-1);

//     while (line[i])
//     {
//         if (line[i] == '\'' && line[i + 1] == '\'')
//             return (i);
//         if (line[i] == '\"' && line[i + 1] == '\"')
//             return (i);
//         i++;
//     }
//     return (-1);
// }