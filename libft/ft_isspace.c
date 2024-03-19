/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:47:04 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/21 21:33:13 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//The isspace() function tests for a space type character (tabs,returns, etc.)

int     ft_isspace(int c)
{
        if ((c > 8 && c < 14) || c == 32)
                return (1);
        else
                return (0);
}


// int	check_emptyorspace(t_shell_sack *sack, char *str)
// {
// 	int	i;
// 	int	space;

// 	i = 0;
// 	space = 0;
// 	if (!str || str == NULL)
// 		return (1);	
// 	while (str[i])
// 	{
// 		if (ft_isspace(str[i]))
// 			space++;
// 		i++;
// 	}
// 	if (i == space)
// 		return (1);
// 	return (0);
// }

int	check_emptyorspace(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (!str || str == NULL)
		return (1);	
	while (str[i])
	{
		if (ft_isspace(str[i]))
			space++;
		i++;
	}
	if (i == space)
		return (1);
	return (0);
}