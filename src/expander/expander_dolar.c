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

/*@brief Alloca memoria. Recibe la variable a expandir ej: USER=cmateos-
return la variable a expandir. Ej: cmateos- */
char *get_varcontent(char *var)
{
	char *var_expanded;
	int	i;

	i = search_char(var, '=', 0);
	var_expanded = ft_substr(var, (i + 1), (ft_strlen(var) - i));
	if (!var)
		return (NULL);
	// printf("var_expandIO:%s\n", var_expanded);
	return (var_expanded);
}

char *get_varname(t_shell_sack *sack, char **old, int i)
{
	char *new_var;

	new_var = ft_substr(old[i], 1, ft_strlen(old[i]));
	if (!new_var)
		return (NULL);
	sack->pos = search_env_pos(sack->env->env, new_var, '\0');
    free (new_var);
	// printf("pos: %d\n", sack->pos);
	if (sack->pos >= 0)
	{
		new_var = get_varcontent(sack->env->env[sack->pos]);
		if (!new_var)
			return (NULL); //proteger aqui
	}
	else
	{
		new_var = (char *)malloc(1 * sizeof (char));
		if (!new_var)
			return (NULL);
		new_var[0] = '\0';
	}
	// new_var = ft_calloc(1, sizeof(char *));
    return (new_var);
}

char **realloc_split_line(t_shell_sack *sack, char **old, int i)
{
    int index;
    char **new;
    char *new_var;

    new_var = get_varname(sack, old, i);
    if (!new_var)
        return (NULL);
    // printf("new_var: %s\n", new_var);
	new = (char **)malloc((ft_arraylen(old) + 1) * sizeof(char *));
	if (!new)
		return (free(new_var), NULL); //pproteger y free arr aqui
	index = 0;
	while (old[index])
	{	
		// printf("pos:%d, i:%d\n", pos, i);
		if (index == i) ///no va encontrar pos cuando la variable no exista en el env
			new[index] = ft_substr(new_var, 0, ft_strlen(new_var));
		else
			new[index] = ft_strdup(old[index]);
		if (!new[index])
			return (ft_free_error_arr(new, index), free(new_var),  NULL); // (ft_free_error_arr(arr, i), ft_free_env(arr), NULL);
		index++;
	}
	new[index] = NULL;
    free(new_var);
	return (new);
}

int expand_dolar(t_shell_sack *sack)
{
    int i;
	int len;
	char **split_line;
	char **temp;

    split_line = ft_split(sack->l_expanded, ' ');
	if (!split_line)
		return (1);
	len = ft_arraylen(split_line);

	i = 0;
	temp = split_line;

    while (len-- >= 0)
    {
        if (temp[i] && temp[i][0] == '$') // check_valid_expanddolar(parseo)
        {
            temp = realloc_split_line(sack, split_line, i);
            if (!temp)
                return (1); //LIBERAR ???
            // printf("Este es temp despues de la vuelta num %d\n", i);
            ft_free_env(split_line);
            split_line = temp;
	         // print_env(split_line);
            i = 0;
        }
        i++;
    }

    free(sack->l_expanded);
	char *temp_var;
	len = ft_arraylen(split_line);
	// printf("len array:%d\n", len);
	i = 1;
	sack->l_expanded = ft_strdup(split_line[0]);
	while (len-- > 1)
	{
		// temp_var = sack->l_expanded;
		temp_var = ft_strjoin(sack->l_expanded, " ");
		free(sack->l_expanded);
		sack->l_expanded = ft_strjoin(temp_var, split_line[i]);
		free(temp_var);
		i++;
	}
	ft_free_env(split_line);
    return (0);
}