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
	if (!var_expanded)
		return (NULL);
	// printf("var_expandIO:%s\n", var_expanded);
	return (var_expanded);
}

char *remove_quotes_get_varname(char *old)
{
	char	*temp;
	char	*var = strdup(old);
	free (old);
	int		len;

	printf("var:%s\n", var);
	printf("VAR[0]:%c\n", var[0]);
	printf("VAR[LEN]:%c\n", var[ft_strlen(var) - 1]);
	if (var[0] == '\"' || var[0] == '\'')
	{
		len = 1;
		if (var[ft_strlen(var) - 1] == '\"' || var[ft_strlen(var) - 1] == '\'')
		{	
			// len++;
		
		}
		// printf("KOSOOOOOOOO");
		// printf("len:%ld\n", ft_strlen(var));
		// temp = ft_substr(var, 1, (ft_strlen(var) - len + 1));
		temp = remove_quotes(var, '\"');
		if (!temp)
				return (printf("temp is nuuuuull"), NULL);	
		free (var);
		printf("TEMP:%s\n", temp);
		var = ft_strdup(temp);
		if (!var)
			return (NULL);
		free (temp);
	}
	else
	{
		temp = ft_strdup(var);
		if (!temp);
			return (NULL);
		free (var);
		var = ft_strdup(temp);
		if (!var)
			return (NULL);
		free (temp);
		
	}
	return (var);
}

char *get_varname(t_shell_sack *sack, char **old, int i)
{
	char *new_var;
	char *temp;

	temp = remove_quotes_get_varname(old[i]);
	if (!temp)
		return (NULL);
	
	new_var = ft_substr(temp, 1, ft_strlen(temp));
	if (!new_var)
		return (NULL);
	free (temp);
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
	int check = 2;

    new_var = get_varname(sack, old, i);
	if (!new_var)
		return (NULL);
    if (new_var[0] == '\0')
        check--;
    // printf("new_var: %s\n", new_var);
	new = (char **)malloc((ft_arraylen(old) + check) * sizeof(char *));
	if (!new)
		return (free(new_var), NULL); //pproteger y free arr aqui
	index = 0;
	while (old[index])
	{	
		// printf("pos:%d, i:%d\n", pos, i);
		if (index == i) ///no va encontrar pos cuando la variable no exista en el env
			new[index] = ft_strdup(new_var);
		// if (index == i && check == 1) ///no va encontrar pos cuando la variable no exista en el env
		// 	new[index] = ft_strdup(new_var);
		else
			new[index] = ft_strdup(old[index]);
		if (!new[index])
			return (ft_free_error_arr(new, index), free(new_var),  NULL); // (ft_free_error_arr(arr, i), ft_free_env(arr), NULL);
		index++;
	}
	new[index] = NULL;
    // free(new_var);
	return (new);
}


void	*arr_to_string(t_shell_sack *sack,char **split_line)
{
	char	*temp_var;
	int		len;
	int		i;

	len = ft_arraylen(split_line);
	// printf("len array:%d\n", len);
	i = 1;
	sack->l_expanded = ft_strdup(split_line[0]);
	if (!sack->l_expanded)
		return (NULL); //SALIDA DE ERROREs?
	while (len-- > 1)
	{
		// temp_var = sack->l_expanded;
		temp_var = ft_strjoin(sack->l_expanded, " ");
		if (!temp_var)
			return (NULL);
		free(sack->l_expanded);
		sack->l_expanded = ft_strjoin(temp_var, split_line[i]);
		if (!sack->l_expanded)
			return (NULL);
		free(temp_var);
		i++;
	}
}


int expand_dolar(t_shell_sack *sack)
{
    int		i;
	int		j;
	char	**split_line;
	char	**temp;
	int		is_string = 1;
	int		expander = 0;

    split_line = ft_split(sack->line, ' ');
	if (!split_line)
		return (1);
	// len = ft_arraylen(split_line);
	i = 0;
	j = 0;
	// temp = split_line;
    while (i < ft_arraylen(split_line))
    {
		while (j < ft_strlen(split_line[i]))
		{
			printf("%c\n", split_line[i][j]);
			if (split_line[i][j] == '\"')
				is_string = !is_string;
			else if (split_line[i][j] == '\'')
				expander = !expander;
			else if ((split_line[i][j] == '$') && (is_string == 1 || expander == 0)) // check_valid_expanddolar(parseo)
			{
				printf("DENTRO: %c\n", split_line[i][j]);
				temp = realloc_split_line(sack, split_line, i);
				if (!temp)
					return (1); //LIBERAR ???
				// printf("Este es temp despues de la vuelta num %d\n", i);
				// ft_free_env(split_line);
				split_line = ft_sarrcpy(temp);
				free (temp);
				print_env(split_line);
				// i = 0;
			}
			j++;
		}
		j = 0;
        i++;
    }

    arr_to_string(sack, split_line);
	ft_free_env(split_line);
	if (!sack->l_expanded)
		return 1;
    return (0);
}

// int expand_dolar(t_shell_sack *sack)
// {
//     int i;
// 	int len;
// 	char **split_line;
// 	char **temp;
// 	int	is_string = 0;
// 	int expander = 0;

//     split_line = ft_split(sack->line, ' ');
// 	if (!split_line)
// 		return (1);
// 	len = ft_arraylen(split_line);

// 	i = 0;
// 	temp = split_line;

//     while (len-- >= 0)
//     {
//         if (temp[i] && temp[i][0] == '$') // check_valid_expanddolar(parseo)
//         {
//             temp = realloc_split_line(sack, split_line, i);
//             if (!temp)
//                 return (1); //LIBERAR ???
//             // printf("Este es temp despues de la vuelta num %d\n", i);
//             ft_free_env(split_line);
//             split_line = temp;
// 	         // print_env(split_line);
//             i = 0;
//         }
//         i++;
//     }

//     arr_to_string(sack, split_line);
// 	ft_free_env(split_line);
// 	if (!sack->l_expanded)
// 		return 1;
//     return (0);
// }