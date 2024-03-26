/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:11:28 by daviles-          #+#    #+#             */
/*   Updated: 2023/04/01 18:41:33 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//duplicate an array of strings. If array is null, returns NULL. 

char	**ft_sarrcpy(char **arr)
{
	int		i;
	char	**new_arr;

	if (!arr)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (ft_sarrlen(arr) + 1));
	if (!new_arr)
		return (NULL);
	i = -1;
	while (arr[++i])
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = NULL;
	return (new_arr);
}
