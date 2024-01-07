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
#include "../../include/minishell.h"
/*@brief Libera las lineas previas malokeadas en caso de error.
@param mem array a liberar
@param i linea donde ocurrió el error
*/
void	ft_free_error_arr(char **mem, long i)
{
    while (i > 0)
        free(mem[--i]);
    free(mem);
}

//@brief libera el array pasado por parametro
void ft_free_env(char **env)
{
	int i;
	
	i = -1;
	if (!env)
		return ;
	while (env[++i])
		free(env[i]);
	free(env);
}

//@brief Print enviroment
int print_env(t_shell_sack ****sack_orig)
{
	t_shell_sack    **sack;
	int 	i;

    sack = (**sack_orig);
	i = 0;
	if (!(*sack)->env->env || !(*sack)->env->env[i])
		return (1);
	while ((*sack)->env->env[i])
	{
		if ((*sack)->env->env[i])
		{
			ft_putstr_fd((*sack)->env->env[i], 1);
			ft_putstr_fd("\n", 1);
		}
			// printf("%d  %s\n", i, (*sack)->env->env[i]);
		i++;
	}
	// if ((*sack)->new_pipes[1] != 1 )
    // 	if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
	// 		free_exit(&(**sack_orig));
	return (0);
}

//@brief Return len array.
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

//@brief Busca si una variable existe en el enviroment
//@param limit delimitador (caracter) hasta el cual comparar si existe (limit inclusive)
//@return El número de línea en la que aparece la variable, -1 si no la encuentra.
int	search_env_pos(char **env, char *word, char limit)
{
	size_t i = -1;
	size_t j = 0;

	if (!env || !word || word[0] == '\0')
		return (-1);
	while ((word[j] && word[j] != limit))
		j++;
	if (limit == '\0')
		j = ft_strlen(word);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], word, j))
		{
			// printf("\nCHAR:%c", env[i][j]);
			if (env[i][j] == '=' || env[i][j] == '\0')
				return (i);
		}
	}
	return (-1);
}
 