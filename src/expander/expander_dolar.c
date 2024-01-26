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

char *expand_dolar(t_shell_sack *sack, char *old, int dolar)
{
    char *pre_expand = NULL;
	char *expand = NULL;
    char *post_expand = NULL;
	char *temp;
	int i = 0;
	int len = 0;

	if (dolar > 0)
		pre_expand = ft_substr(old, 0, dolar);
	i = dolar + 1;
	if (old[i] == '?')
	{
		expand = ft_itoa(sack->last_exit);
		i++;
	}
	else
	{
		len = len_expand_dolar(old, i);
		temp = ft_substr(old, i, len);
		i += len;
		// printf("len:%d\n", len);
		// printf("temp:%s\n", temp);
		expand = get_varname(sack, temp);
		free (temp);
	}
	// printf("\nexpand:%s\n", expand);
	if ((size_t)i < ft_strlen(old))
	{
		post_expand = ft_substr(old, i, ft_strlen(old));
		// printf("\npost_expand:%s\n", post_expand);
	}
	if (pre_expand)
	{
		// printf("\npre_expand:%s\n", pre_expand);
		temp = ft_strjoin(pre_expand, expand);
		free (pre_expand);
		free(expand);
		expand = ft_strdup(temp);
		free (temp);
	}
	if (post_expand)
	{
		temp = ft_strjoin(expand, post_expand);
		free (expand);
		free (post_expand);
		expand = ft_strdup(temp);
		free (temp);
	}
	// printf("expand:%s\n", expand);
	return (expand);
}
