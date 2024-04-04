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
#include "../../include/minishell.h"

void	remove_quotes_arr_cmds(t_token *token, t_shell_sack **sack)
{
	char	*temp;
	size_t	i;

	if (!token->cmds)
		return ;
	i = 0;
	while (i < ft_sarrlen(token->cmds))
	{
		temp = remove_quotes_cmd(token->cmds[i]);
		if (!temp)
			return (free_exit(token->cmds, &sack, 0));
		free(token->cmds[i]);
		token->cmds[i] = ft_strdup(temp);
		free (temp);
		if (!token->cmds[i])
			return (free_exit(token->cmds, &sack, 0));
		i++;
	}
}

char	*remove_quotes_cmd(char *s)
{
	char	*cmd;
	int		i;

	i = -1;
	cmd = NULL;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == D_QUOTES)
		{
			cmd = remove_quotes(s, D_QUOTES, 0);
			return (cmd);
		}
		else if (s[i] == S_QUOTES)
		{
			cmd = remove_quotes(s, S_QUOTES, 0);
			return (cmd);
		}
	}
	if (!cmd)
		cmd = ft_strdup(s);
	return (cmd);
}

/*@brief aloca memoria para una copia sin comillas
@param old la string a copiar
@param type el tipo de comillas a eliminar, simples o dobles
@return string sin comillas, NULL en caso de error*/
char	*remove_quotes(char *old, char type, int quotes)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i++ < ft_strlen(old))
	{
		if (old[i] == type)
			quotes++;
	}
	new = (char *)malloc((i - quotes + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[i - quotes - 1] = '\0';
	i = 0;
	while (i < (ft_strlen(old) - quotes))
	{
		if (old[j] == type)
			j++;
		else
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
