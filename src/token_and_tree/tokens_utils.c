/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// @brief This function fix the name of the redirection file, 
//taking off operator and spaces. @return Returns char* with fixed name.
char	*fix_tokenvalues(char **value)
{
	char	*aux;

	aux = ft_strtrim(*value, "<> ");
	free (*value);
	return (aux);
}

int	get_token_type(char *value)
{
	int	i;

	i = 0;
	if (!ft_strncmp(value, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(value, "<<", 2))
		return (HEREDOC);
	else if (value[i] == '<')
		return (REDIR_IN);
	else if (!ft_strncmp(value, ">>", 2))
		return (APPEND_OUT);
	else if (value[i] == '>')
		return (REDIR_OUT);
	else if (!ft_strncmp(value, "&&", 3) || !ft_strncmp(value, "||", 3))
		return (OPER);
	else if (value[i] == '(')
		return (PARENT_OP);
	else if (value[i] == ')')
		return (PARENT_CL);
	else
		return (CMD);
}

int	find_nextquote(char *str, char quote)
{
	int	i;
	int	closed;

	i = 0;
	closed = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
		{
			closed = 1;
			break ;
		}
		i++;
	}
	if (closed)
		return (i);
	else
		return (-1);
}

/* @brief This function is used to save redirection operator with filename in 
token value. */
// @return Doesn't return anything because moves the iterator pointer
void	save_redir_filename(char *line, int *i)
{
	*i = *i + 1;
	if (line[*i] == '<' || line[*i] == '>')
		*i = *i + 1;
	if (ft_isspace(line[*i]))
	{
		while (ft_isspace(line[*i]) && line[*i] != '\0')
			*i = *i + 1;
	}
	while (ft_isalnum(line[*i]) || line[*i] == '.' || line[*i] == '_'
		|| line[*i] == '-' || line[*i] == '/' || line[*i] == '\''
		|| line[*i] == '\"' || line[*i] == '$')
	{
		*i = *i + 1;
	}
}

void	get_cmd_args(t_shell_sack **sack)
{
	t_token	*token;
	t_dlist	*token_list;

	token_list = (*sack)->token_list;
	while (token_list)
	{
		token = token_list->content;
		if (token->type == CMD)
			token->cmds = ft_split_minishell(token->value);
		else
			token->cmds = ft_split("NULL", ' ');
		token_list = token_list->next;
	}
}
