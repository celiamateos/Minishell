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
// FUNCIONA PERO HAY QUE PROTEGER LOS MALLOCS Y EXPANDIR LAS COMILLAS JEJE

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
	char *new_var;
	int pos;


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

int	check_expand_dolar(char *old, int i)
{
	if (!old[i + 1] || old[i + 1] == '\"' || old[i + 1] == '\'' || isspace(old[i + 1]))
		return (1);
	if ((ft_isalpha(old[i + 1] && ft_isdigit(old[i + 1]) && old[i + 1] != '?' )))
		return (1);
	return (0);
}

char *expand_dolar(t_shell_sack *sack, char *old, int dolar)
{
    char *pre_expand = NULL;
	char *expand = NULL;
    char *post_expand = NULL;
	char *temp;
	int i;
	int start;
	size_t len = 0;
	
	if (dolar > 0)
		pre_expand = ft_substr(old, 0, dolar);
	
	start = dolar + 1;
	i = dolar;
	while (old[i] && old[i] != D_QUOTES && old[i] != S_QUOTES
	&& old[i] != '?' && !ft_isspace(old[i]))
	{
		i++;
		len++;
	}
	// if (old[i] == D_QUOTES || old[i] == S_QUOTES)
	len--;
	// printf("\nlen:%ld\n", len);
	temp = ft_substr(old, start, len);
	if (old[dolar + 1] == '?')
	{
		expand = ft_itoa(sack->last_exit);
		len++;
		i++;
	}
	else
   		expand = get_varname(sack, temp);
	free (temp);
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
