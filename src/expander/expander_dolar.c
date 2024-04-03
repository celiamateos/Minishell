/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dolar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:47:48 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/09 16:47:49 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
// FUNCIONA PERO HAY QUE PROTEGER LOS MALLOCS Y CORTAR PA LA NORMINETTE

/*@brief Alloca memoria. Recibe la variable a expandir ej: USER=cmateos-
return la variable a expandir. Ej: cmateos- */
char *get_varcontent(char *var)
{
	char *var_expanded;
	int	i;

	i = search_char(var, '=', 0);
	var_expanded = ft_substr(var, (i + 1), (ft_strlen(var) - i));
	if (!var_expanded)
		return (NULL);
	// printf("var_expandIO:%s\n", var_expanded);
	return (var_expanded);
}

/*@Brief ALOCA MEMORIA JODER
TOMA UNA PALABRA E INTENTA EXPANDIRLA BUSCANDOLA EN ENVIROMENT Y EN PRE EXPORT
SI NO LA ENCUENTRA RETORNA UNA STRING VACÍA*/
char *get_varname(t_shell_sack *sack, char *old)
{
	char	*new_var;
	int		pos;

	new_var = NULL;
	// printf("\nold:%s\n", temp);
	pos = search_env_pos(sack->env->env, old, '=');
	if (pos >= 0)
	{
		// printf("PUTO POS:%d", pos);
		if (!sack->env->env[pos])
			return (NULL);
		new_var = get_varcontent(sack->env->env[pos]);
		if (!new_var)
			return (NULL); //proteger aqui
	}
	else
	{
		pos = search_env_pos(sack->env->pre_export, old, '=');
		if (pos >= 0)
		{
			if (!sack->env->pre_export[pos])
				return NULL;
			new_var = get_varcontent(sack->env->pre_export[pos]);
			if (!new_var)
				return (NULL); //proteger aqui
		}
		else
			new_var = ft_strdup("");
	}
    return (new_var);
}

int	len_expand_dolar(char *old, int i)
{
	int	len;

	len = 0;
	if (old[i] == '\0')
		return (len);
	if (!ft_isalpha(old[i]))
		return (1);
	len++;
	while (old[++i])
	{
		if (old[i] == '$')
			return (len);
		if (!ft_isalnum(old[i]) && old[i] != '_')
			return (len);
		len++;
	}
	return (len);
}

char *arr_join_not_spaces(t_shell_sack *sack)
{
	char *temp = NULL;
	char *expand;

	if (sack->expanded[0] && sack->expanded[0][0] != '\0')
		temp = ft_strjoin (sack->expanded[0], sack->expanded[1]);
	if (temp)
		expand = ft_strjoin(temp, sack->expanded[2]);
	else
		expand = ft_strdup(temp);
	if (temp)
		free (temp);
	return (expand);
		// pre_expand = ft_strdup(sack->expand[0]);
	
}

char *previous_expand_dolar(t_shell_sack *sack, char *old, int dolar)
{
	if (dolar > 0)
		sack->expanded[0] = ft_substr(old, 0, dolar);
	else
		sack->expanded[0] = ft_strdup("\0");
	if (!sack->expanded[0])
		return (NULL);
	return (sack->expanded[0]);
}

int	run_expand_dolar(t_shell_sack *sack, char *old, int dolar)
{
	int	i;
	char *temp;
	char *expand;

	expand = NULL;
	temp = NULL;
	i = dolar + 1;
	if (old[i] == '?')
	{
		sack->expanded[1] = ft_itoa(sack->last_exit);
		i++;
	}
	else
	{
		temp = ft_substr(old, i, len_expand_dolar(old, i));
		i += len_expand_dolar(old, i);
		sack->expanded[1] = get_varname(sack, temp);
		free (temp);
	}
	return (i);
}

char *expand_dolar(t_shell_sack *sack, char *old, int dolar)
{
	char *expand = NULL;
	int i;

	sack->expanded = malloc(4 * sizeof(char *));
	if (!sack->expanded)
		return (NULL);
	sack->expanded[0] = previous_expand_dolar(sack, old, dolar);
	if (!sack->expanded[0])
		return (ft_free_error_arr(sack->expanded, 0), NULL);
	i = run_expand_dolar(sack, old, dolar);
	if (!sack->expanded[1])
		return (ft_free_error_arr(sack->expanded, 1), NULL);
	if ((size_t)i < ft_strlen(old))
		sack->expanded[2] = ft_substr(old, i, ft_strlen(old));
	else
		sack->expanded[2] = ft_strdup("\0");
	if (!sack->expanded[2])
		return (ft_free_error_arr(sack->expanded, 2), NULL);
	sack->expanded[3] = NULL;
	expand = arr_join_not_spaces(sack);
	ft_free_env(sack->expanded);
	if (!expand)
		return (NULL);
	return (expand);
}
