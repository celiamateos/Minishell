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


char *get_varname(t_shell_sack *sack, char *old)
{
	char *new_var;
	char *temp;
	int pos;

	// new_var = ft_strtrim(old, "$\'\"");
	// printf("old:%s\n", old);
	// printf("FldLo:%s\n", sack->env->env[0]);
	// print_env(sack->env->env);
	// exit(1);
	pos = search_env_pos(sack->env->env, old, '=');
	// free (new_var);
	// printf("pos: %d\n", pos);
	// exit(1);
	if (pos >= 0)
	{
		if (!sack->env->env[pos])
			return NULL;
		new_var = get_varcontent(sack->env->env[pos]);
		if (!new_var)
			return (NULL); //proteger aqui
	}
	 else
		new_var = ft_strdup("");

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
	// printf("len:%d\n", len);
	temp = ft_substr(old, start, len);
	// printf("expand antes de getvarname:%s\n", temp);
    expand = get_varname(sack, temp);
	free (temp);

	if (i < ft_strlen(old))
	{
		post_expand = ft_substr(old, i, ft_strlen(old));

	}

	// printf("pre_expand:%s\n", pre_expand);
	// printf("expand:%s\n", expand);
	// printf("post_expand:%s\n", post_expand);
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

	// printf("new var control:%s\n", expand);
	// exit(1);
	return (expand);

}

// int expand_dolar(t_shell_sack *sack)
// {
//     int		i;
// 	char *	temp;
// 	int		expander = 1;

// 	sack->d_quotes = 0;
// 	sack->s_quotes = 0;
// 	i = 0;
// 	while (sack->line[i++])
// 	{
// 		if (sack->line[i] == D_QUOTES)
// 		{
// 			sack->d_quotes = !sack->d_quotes;
// 		}
// 		if (sack->line[i] == S_QUOTES)
// 		{
// 			if (sack->d_quotes == 0)
// 				expander = !expander;
// 			sack->s_quotes = !sack->s_quotes;
// 		}
// 		if ((sack->line[i] == '$') && (expander == 1)) // check_valid_expanddolar(parseo) x ejemplo q no haya espacio antes del $
// 		{
// 			temp = realloc_expand_dolar(sack, sack->line, i);		
// 		}
//     }
// 	if (!sack->l_expanded)
// 		return 1;
//     return (0);
// }

// /*@brief ALOCA MEMORIA. Concatena cada linea del array split_line y retorna un char **/
// void	*arr_to_string(t_shell_sack *sack,char **split_line)
// {
// 	char	*temp_var;
// 	int		len;
// 	int		i;

// 	if (!split_line)
// 		return (NULL);
// 	len = ft_arraylen(split_line);
// 	// printf("len array:%d\n", len);
// 	i = 1;
// 	sack->l_expanded = ft_strdup(split_line[0]);
// 	if (!sack->l_expanded)
// 		return (NULL); //SALIDA DE ERROREs?
// 	while (len-- > 1)
// 	{
// 		// temp_var = sack->l_expanded;
// 		temp_var = ft_strjoin(sack->l_expanded, " ");
// 		if (!temp_var)
// 			return (NULL);
// 		free(sack->l_expanded);
// 		if (split_line[i])
// 		{
// 			sack->l_expanded = ft_strjoin(temp_var, split_line[i]);
// 			if (!sack->l_expanded)
// 				return (NULL);
// 		}
// 		else
// 		{
// 			sack->l_expanded = ft_strjoin(temp_var, "");
// 			if (!sack->l_expanded)
// 				return (NULL);
// 		}
// 		free(temp_var);
// 		i++;
// 	}
// }

// char *remove_quotes_get_varname(char *var)
// {
// 	char	*temp;
// 	int		len = 0;
// 	int		i = 0;
// 	int		j = 0;

// 	// len = ft_strlen(var);
// 	printf("PUTA VAAAR: %s\n", var);
// 	while (var[i++])
// 	{
// 		if (var[i] != '\'' || var[i] != '\"')
// 			len++;
// 	}
// 	temp = (char *)malloc((len + 1) * sizeof(char));
// 	i = 0;
// 	while (var[i++])
// 	{
// 		if (var[i] == '\'' || var[i] == '\"')
// 			i++;
// 		else
// 			temp[j++] = var[i];
// 	}
// 	temp[j] = '\0';
// 	printf("temp yeahhhh:%s\n", temp);
// 	return (temp);
// }