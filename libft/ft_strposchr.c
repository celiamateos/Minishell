/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strposchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:29:23 by karsp             #+#    #+#             */
/*   Updated: 2023/11/21 21:34:40 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_strposchr(const char *s, int c)
{
        int             count;

        count = 0;
        if (s)
        {
                while (((char *) s)[count] != '\0')
                {
                        if (((char *) s)[count] == (char) c)
                                return (count);
                        count++;
                }
        }
        return (-1);
}