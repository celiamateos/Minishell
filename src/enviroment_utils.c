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
	if (!array)
		return(i);
	while (array[i])
		i++;
	return (i);
}



//Siver para buscar si una variable existe en el enviroment
//Busca una variable en una función. (busca hasta el = iclusive)
// Retorna el número de línea en la que aparece la variable, -1 si no la encuentra.
int	search_env_pos(char **env, char *word, char limit)
{
	size_t i = -1;
	size_t j = 0;

	if (!env || !word)
		return (-1);
	while ((word[j] != limit && word[j]))
		j++;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], word, j))
		{
			printf("CHAR: %c", env[i][j]);
			if (env[i][j] == '=' || env[i][j] == '\0')
			return (i);
		}
	}
	return (-1);
}
