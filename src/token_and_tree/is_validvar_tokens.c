/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_validvar_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:53:52 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/05 22:53:54 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	valid_varformat(char *value, int *i)
{
	if (ft_isspace(value[*i]))
		while (ft_isspace(value[*i]))
			*i = *i + 1;
	if (!ft_isalpha(value[*i]))
		return (0);
	else
		*i = *i + 1;
	while (value[*i] != '\0')
	{
		if (ft_isspace(value[*i]))
			return (0);
		else if (value[*i] == '=')
			break ;
		else
			*i = *i + 1;
	}
	if (value[*i] != '=')
		return (0);
	*i = *i + 1;
	if (ft_isspace(value[*i]))
		return (0);
	return (1);
}

int	valid_varname(char *value, int *i)
{
	if (ft_isspace(value[*i]))
		while (ft_isspace(value[*i]))
			*i = *i + 1;
	if (!ft_isalpha(value[*i]))
		return (0);
	else
		*i = *i + 1;
	while (value[*i] != '\0')
	{
		if (ft_isalnum(value[*i]) || value[*i] == '_')
			*i = *i + 1;
		else if (value[*i] == '=')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	isvalid_var(char *value)
{
	int	i;

	i = 0;
	if (!valid_varformat(value, &i))
		return (0);
	i = 0;
	if (!valid_varname(value, &i))
		return (0);
	return (1);
}
