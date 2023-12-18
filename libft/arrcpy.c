/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:52:58 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/14 11:53:22 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "../include/minishell.h"

//Copy one string array
char	**ft_sarrcpy(char **arr)
{
	int		i;
	char	**new_arr;

	if (!arr)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (ft_arraylen(arr) + 1));
	i = -1;
	while (arr[++i])
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = NULL;
	return (new_arr);
}

