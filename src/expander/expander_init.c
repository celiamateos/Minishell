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

int	check_expand_dolar(t_shell_sack *sack, int i)
{
	if ((sack->line[i] && sack->line[i] == '$') && (sack->expander == 1)
		&& sack->line[i + 1] != '\0' && ft_isspace(sack->line[i + 1]) == 0
		&& sack->line[i + 1] != D_QUOTES && sack->line[i + 1] != S_QUOTES)
		return (1);
	return (0);
}

char	*reset_expander(t_shell_sack *sack, char *temp)
{
	free(sack->line);
	sack->line = ft_strdup(temp);
	free (temp);
	if (!sack->line)
		return (NULL);
	sack->d_quotes = 0;
	sack->s_quotes = 0;
	sack->expander = 1;
	return (sack->line);
}

int	reset_quotes_expand_line(t_shell_sack **sack)
{
	(*sack)->d_quotes = 0;
	(*sack)->s_quotes = 0;
	(*sack)->expander = 1;
	return (-1);
}

char	*start_expand_line(t_shell_sack *sack, int i)
{
	char	*temp;

	while (sack->line[++i])
	{
		if (sack->line[i] && sack->line[i] == '\"' && sack->s_quotes == 0)
			sack->d_quotes = !sack->d_quotes;
		else if (sack->line[i] && sack->line[i] == '\'' && sack->d_quotes == 0)
		{
			if (sack->d_quotes == 0)
				sack->expander = !sack->expander;
			sack->s_quotes = !sack->s_quotes;
		}
		else if (sack->line[i] && check_expand_dolar(sack, i) == 1)
		{
			temp = expand_dolar(sack, sack->line, i);
			if (temp)
			{
				sack->line = reset_expander(sack, temp);
				if (!sack->line)
					return (NULL);
			}
			i = reset_quotes_expand_line(&sack);
		}
	}
	return (sack->line);
}

int	expand_line(t_shell_sack *sack)
{
	int		i;
	char	*temp;

	i = 0;
	reset_quotes_expand_line(&sack);
	sack->line = start_expand_line(sack, i - 1);
	if (!sack->line)
		return (1);
	temp = ft_strtrim(sack->line, " \t\v\n\r");
	sack->l_expanded = ft_strdup(temp);
	free (temp);
	if (!sack->l_expanded)
		return (1);
	return (0);
}
