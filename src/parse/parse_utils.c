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


int	check_emptystr(t_shell_sack *sack, size_t i)
{
    if (!sack->line || i > ft_strlen(sack->line))
        return (-1);

    while (sack->line[i])
    {
        if (sack->line[i] == '\'' && sack->line[i + 1] == '\'')
            return (i);
        if (sack->line[i] == '\"' && sack->line[i + 1] == '\"')
            return (i);
        i++;
    }
    return (-1);
}

int check_open_quotes(t_shell_sack *sack, char *s)
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

//NO SE USA PERO VAYA JEJE
/*@brief ALOCA MEMORIA.
Recibe una string y aloca memoria para una copia
en la que elimina una parte de la string
@param start inicio de la parte a eliminar
@param lenn final de la parte a eliminar*/
char *remove_partofstr(const char *s, size_t start, size_t len)
{
    // size_t	original_len;
	size_t	i;
	size_t	j;
	char*	new;

	i = 0;
	j = 0;
    if (!s || !len)
        return (NULL);
	// original_len = ft_strlen(s);
    if (start >= ft_strlen(s) || (start + len) > ft_strlen(s))
        return (NULL);
    new = (char *)malloc((ft_strlen(s) - len + 1) * sizeof(char));
    if (!new)
        return NULL;
    while (s[i] != '\0')
    {
        if (i >= start && i < (start + len))
            i++;
        else
            new[j++] = s[i++];
    }
    new[j] = '\0';
    return new;
}