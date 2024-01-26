/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:10:41 by cmateos-          #+#    #+#             */
/*   Updated: 2023/04/12 18:33:26 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	ft_putstr_fd_noquotes(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
			{
				// printf("%c", s[i]);
				write (fd, &s[i], 1);
				i++;
			}
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"')
			{
				write (fd, &s[i], 1);
				i++;
			}
		}
		else
			write (fd, &s[i], 1);
	}
}

