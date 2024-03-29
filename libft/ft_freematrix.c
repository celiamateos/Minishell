/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:23:20 by daviles-          #+#    #+#             */
/*   Updated: 2023/08/31 18:48:22 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_freematrix(char ***matrix)
{
	int	i;

	i = 0;
	if (*matrix)
	{
		while ((*matrix)[i] != NULL)
		{
			free((*matrix)[i]);
			i++;
		}
		free(*matrix);
		*matrix = NULL;
	}
}
