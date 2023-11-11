/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:15:07 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/10 09:15:08 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

//Libera struct env y el env array.
//se puede meter dentro de otra despues.
void ft_free_env(char **env)
{
	int i = -1;
	if (env)
	{
		while (env[++i])
			free(env[i]);
		free(env);
	}
}

// Print enviroment
void print_env(char **env)
{
	int i = 0;

	printf("\n");
	if (!env)
		return ;
	while (env[i])
	{
		printf("line:%d  %s\n", i, env[i]);
		i++;
	}
}

//Return len array.
size_t ft_arraylen(char **array)
{
	size_t i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

//Verificar si incluye la variable en enviroment, si no muestra un error.
//True si es valido para exportar: Ej export VARIABLE="contenido"
//False si no es valido. Ej export 13fabVAR = "hola"
int is_valid_to_export(char *s)
{
	int i;

    i = 0;
	if (!ft_isalpha(s[i]))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && !ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	if (s[i] != '=' || s[i] == '\0')
		return (0);
	return (1);
}

//Busca una variable en una función.
// Retorna 0 si la variable no existe
// Retorna 1 si la variable ya existe y hay que sustituirla.
//Retorna -1 si el env no existe, o sea ERROR.
// Retorna el número de línea en la que aparece la variable, -1 si no la encuentra.
int	search_env(char **env, char *word)
{
	int i = -1;
	int j = 0;

	if (!env || !word)
		return (-1);
	while (env[++i])
	{
		while (env[i][j] == word[j] && env[i][j] && word[j] && env[i][j] != '=')
			j++;
		if (env[i][j] == '=' || word[j] == '\0')
			return (i);
		j = 0;
	}
	return (-1);
}
