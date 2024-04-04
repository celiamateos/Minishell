/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dolar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:18:56 by cmateos           #+#    #+#             */
/*   Updated: 2024/04/03 19:18:57 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/*@brief Alloca memoria. Recibe la variable a expandir ej: USER=cmateos-
return la variable a expandir. Ej: cmateos- */
char	*get_varcontent(char *var)
{
	char	*var_expanded;
	int		i;

	i = search_char(var, '=', 0);
	var_expanded = ft_substr(var, (i + 1), (ft_strlen(var) - i));
	if (!var_expanded)
		return (NULL);
	return (var_expanded);
}

char	*get_varname_pre_export(t_shell_sack *sack, char *old)
{
	char	*new_var;
	int		pos;

	pos = search_env_pos(sack->env->pre_export, old, '=');
	if (pos >= 0)
	{
		if (!sack->env->pre_export[pos])
			return (NULL);
		new_var = get_varcontent(sack->env->pre_export[pos]);
	}
	else
		new_var = ft_strdup("");
	if (!new_var)
		return (NULL);
	return (new_var);
}

/*@Brief ALOCA MEMORIA JODER
TOMA UNA PALABRA E INTENTA EXPANDIRLA BUSCANDOLA EN ENVIROMENT Y EN PRE EXPORT
SI NO LA ENCUENTRA RETORNA UNA STRING VACÍA*/
char	*get_varname(t_shell_sack *sack, char *old)
{
	char	*new_var;
	int		pos;

	pos = search_env_pos(sack->env->env, old, '=');
	if (pos >= 0)
	{
		if (!sack->env->env[pos])
			return (NULL);
		new_var = get_varcontent(sack->env->env[pos]);
		if (!new_var)
			return (NULL);
		return (new_var);
	}
	new_var = get_varname_pre_export(sack, old);
	return (new_var);
}
