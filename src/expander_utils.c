/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

/*@brief aloca memoria para una copia sin comillas
@param old la string a copiar
@param type el tipo de comillas a eliminar, simples o dobles
@return string sin comillas, NULL en caso de error*/
char *remove_quotes(char *old, char type)
{
    char *new;
    int  i = 0;
    int j = 0;
    int quotes = 0;

    if (!old)
        return (NULL);
    while (i++ < ft_strlen(old))
    {
        if (old[i] == type)
            quotes++;
    }
    new = (char *)malloc((i - quotes + 1) * sizeof(char));
    if (!new)
        return (NULL);
    new[i - quotes] = '\0';
    i = 0;
    while (i < (ft_strlen(old) - quotes))
    {
        if (old[j] == type)
            j++;
        new[i++] = old[j++];
    }
    return (new);
}

int	search_char(char *s, char c, int i)
{

	if (!s || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void check_open_quotes(t_shell_sack *sack, char *s)
{
	int i;
	
	i = -1;
	if (!s || s[i + 1] == '\0')
		return ; //No se si hay que proteger aqui.
	while (s[++i])
	{
		if (s[i] == '\"')
		{
			sack->d_quotes = !sack->d_quotes;
			if (!search_char(s, '\"', i + 1))
				break ;
			i = search_char(s, '\"', i + 1);
			sack->d_quotes = !sack->d_quotes;
		}
		else if (s[i] == '\'')
		{
			sack->s_quotes = !sack->s_quotes;
			if (!search_char(s, '\'', i + 1))
				break ;
			i = search_char(s, '\'', i + 1);
			sack->s_quotes = !sack->s_quotes;
		}
	}
}