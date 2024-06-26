/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:12:13 by daviles-          #+#    #+#             */
/*   Updated: 2023/07/03 23:56:11 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"
// #include "libft.h"
void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_saveline(char **waste)
{
	char		*rln;
	char		*tmp;
	int			to;
	size_t		size;

	size = ft_strposchr(*waste, '\n');
	if (ft_strposchr(*waste, '\n') != -1 && size != ft_strlen(*waste))
	{
		to = ft_strposchr(*waste, '\n') + 1;
		rln = ft_substr(*waste, 0, to);
		tmp = *waste;
		*waste = ft_substr(*waste, to, ft_strlen(*waste));
		ft_free(&tmp);
	}
	else
	{
		to = ft_strlen(*waste);
		rln = ft_substr(*waste, 0, to);
		if (*waste)
			ft_free(waste);
	}
	return (rln);
}

int	ft_read(char **waste, int fd)
{
	int		r;
	char	*tmp;
	char	*buf;

	buf = (char *) ft_calloc (BUFFER_SIZE + 1, 1);
	r = 1;
	while (r > 0 && ft_strposchr(buf, '\n') == -1)
	{
		ft_bzero(buf, BUFFER_SIZE);
		r = read(fd, buf, BUFFER_SIZE);
		tmp = *waste;
		*waste = ft_strjoin(*waste, buf);
		ft_free(&tmp);
	}
	ft_free(&buf);
	if (r <= 0)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*waste[MAX_FD];

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0 || fd >= MAX_FD)
	{
		ft_free(&waste[fd]);
		return (0);
	}
	if (waste[fd] == NULL)
		waste[fd] = (char *) ft_calloc (1, 1);
	if (ft_strposchr(waste[fd], '\n') == -1)
	{
		if (ft_read(&waste[fd], fd) == 0)
		{
			if (ft_strlen(waste[fd]) > 0)
			{
				line = waste[fd];
				waste[fd] = NULL;
				return (line);
			}
			ft_free(&waste[fd]);
			return (0);
		}
	}
	return (ft_saveline(&waste[fd]));
}
/*
int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line = "";
	int		i;

	i = 1;
	fd1 = open("test1.txt", O_RDONLY);
	fd1 = open("test1.txt", O_RDONLY);
	line = get_next_line(fd1);
	line = get_next_line(fd2);
	while (line)
	{
		printf("Result %d: %s", i, line);
		free(line);
		line = NULL;
		line = get_next_line(fd1);
		i++;
	}
    close(fd);
//	system("leaks a.out");
	return (0);
}
*/
