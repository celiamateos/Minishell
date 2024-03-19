/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:37:20 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/05 23:37:22 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int expand_line(t_shell_sack *sack)
{
    int		i;
	char	*temp;
	int		expander;
	
	i = 0;
	sack->d_quotes = 0;
	sack->s_quotes = 0;
	expander = 1;
	while (sack->line[i])
	{
		if (sack->line[i] == '\"')
			sack->d_quotes = !sack->d_quotes;
		else if (sack->line[i] == '\'')
		{
			if (sack->d_quotes == 0)
				expander = !expander;
			sack->s_quotes = !sack->s_quotes;
		}
		// else if (sack->line[i] == '*' && sack->d_quotes == 0 && sack->s_quotes == 0)
		// {
		// 	temp = expand_wildcard(sack, sack->line, i);
		// 	free (sack->line);
		// 	sack->line = ft_strdup(temp);
		// 	free (temp);
		// 	i = 0;
		// }
		else if ((sack->line[i] == '$') && (expander == 1)
		&& sack->line[i + 1] != '\0' && ft_isspace(sack->line[i + 1]) == 0
		&& sack->line[i + 1] != D_QUOTES  && sack->line[i + 1] != S_QUOTES) //pensar en mas casos
		{
			temp = expand_dolar(sack, sack->line, i);
			free (sack->line);
			sack->line = ft_strdup(temp);
			free (temp);
			// printf("\nsack->line:%s", sack->line);
			i = -1;
			sack->d_quotes = 0;
			sack->s_quotes = 0;
			expander = 1;
		}
		i++;
    }
	temp = ft_strtrim(sack->line, " \t\v\n\r");
	sack->l_expanded = ft_strdup(temp);
	free (temp);
	if (!sack->l_expanded)
		return (1);
    return (0);
}
