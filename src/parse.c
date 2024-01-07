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
#include"../include/minishell.h"



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

int check_errors_initsack(t_shell_sack *sack)
{
	char *s;
	// char	*temp;
	// int start;
	// int	i = 0;
	// int	is_str = 0;
	// int	is_str2 = 0;
	// s = ft_strdup(sack->line);

	s = sack->line;
	if (check_open_quotes(sack, s))
		return (ft_putstr_fd("Input invalid, found open quotes\n", 2), 1);

	// start = check_emptystr(sack, 0);
	// while (s[i])
	// {
	// 	if (s[i] == '\'') // && s[i + 1] != '\'' )
	// 		is_str = !is_str;
	// 	if (s[i] == '\"')// && s[i + 1] != '\"') 
	// 		is_str2 = !is_str2;
	// 	start = check_emptystr(sack, i);
	// 	if ((start > -1) && (is_str == 0 && is_str2 == 0))
	// 	{

	// 		temp = remove_partofstr(sack->line, start, 2);
	// 		if (!temp)
	// 			return (printf("YA LA ESTAS CAGANDO"), 1);
	// 		free(sack->line);
	// 		sack->line = strdup(temp);
	// 		free (temp);
	// 		i = start;
	// 	}
	// 	i++;
	// }
	// free (s);
	// printf("sack_line en errorinit:%s\n", sack->line);
	return (0);
}