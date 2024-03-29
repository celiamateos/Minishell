/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:51:06 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/07 18:51:07 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//@Brief ALOCA MEMORIA 
/*@param arr recibe un array
@return retorna una string concatenando cada cadena del array con espacios*/
char	*ft_arrtostr(char **arr)
{
	int		i;
	char	*s;
	char	*temp;

	i = 0;
	if (!arr | !*arr)
		return (NULL);
	s = ft_strdup(arr[i]);
	if (!s)
		return (NULL);
	i++;
	while (arr[i])
	{
		temp = ft_strjoin(s, " ");
		if (!temp)
			return (free(s), NULL);
		free (s);
		s = ft_strjoin(temp, arr[i]);
		if (!s)
			return (free(temp), NULL);
		free (temp);
		i++;
	}
	return (s);
}
