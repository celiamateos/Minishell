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

//@brief Free previous allocated if error
//@param mem array to free
//@param i line where it was error
int	ft_free_error_arr(char **mem, long row)
{
	int	i;

	i = 0;
	if (mem[row] == NULL)
	{
		while (i < row)
		{
			free(mem[i]);
			i++;
		}
		free(mem);
		return (1);
	}
	return (0);
}

//@brief free array
void	ft_free_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
		free(env[i]);
	free(env);
}

//@brief Print enviroment
int	print_env(t_shell_sack ****sack_orig)
{
	t_shell_sack	**sack;
	int				i;

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
		i++;
	}
	return (0);
}

//@brief shearch if one variable is into enviroment
//@param limit delimiter up to which to compare if any
//@return the number of the line on which the variable appears, -1 if not found.
int	search_env_pos(char **env, char *word, char limit)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
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
			if (env[i][j] == '=' || env[i][j] == '\0')
				return (i);
		}
	}
	return (-1);
}
