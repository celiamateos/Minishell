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

int	ft_putstr_fd_noquotes_iter(char *s, int fd, int i, int quotes)
{
	i++;
	while (s[i] && s[i] != quotes)
	{
		write (fd, &s[i], 1);
		i++;
	}
	return (i);
}

void	ft_putstr_fd_noquotes(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
			i = ft_putstr_fd_noquotes_iter(s, fd, i, '\'');
		else if (s[i] == '\"')
			i = ft_putstr_fd_noquotes_iter(s, fd, i, '\"');
		else
			write (fd, &s[i], 1);
	}
}
