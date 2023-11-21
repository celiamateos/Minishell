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