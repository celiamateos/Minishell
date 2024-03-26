/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:11:28 by daviles-          #+#    #+#             */
/*   Updated: 2023/04/01 18:41:33 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//duplicate an array of strings. If array is null, returns an empty array. 

//@brief Return len array.
size_t	ft_sarrlen(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i])
		i++;
	return (i);
}
