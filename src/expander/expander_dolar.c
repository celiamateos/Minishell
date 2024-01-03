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

char *get_varname(t_shell_sack *sack, char *old)
{
	char *new_var;
	int pos;

    // echo $? mostrar codigo de error:
	if (!ft_strncmp(old, "?", ft_strlen(old)))
		return (new_var = ft_itoa(sack->last_exit));
	pos = search_env_pos(sack->env->env, old, '=');
	if (pos >= 0)
	{
		if (!sack->env->env[pos])
			return NULL;
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
 
char *expand_dolar(t_shell_sack *sack, char *old, int i)
{
    char *pre_expand = NULL;
	char *expand = NULL;
    char *post_expand = NULL;
	char *temp;
	int start;
	int len = 0;

	if (i > 0)
	{
		pre_expand = ft_substr(old, 0, i);	
	}
	start = ++i;
	len = 0;
	while (old[i] && old[i] != ' ' && old[i] != '\"' && old[i] != '\'')
	{
		len++;
		i++;
	}
	temp = ft_substr(old, start, len);
    expand = get_varname(sack, temp);
	free (temp);
	if ((size_t)i < ft_strlen(old))
	{
		post_expand = ft_substr(old, i, ft_strlen(old));

	}
	if (pre_expand)
	{
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
	return (expand);
}
