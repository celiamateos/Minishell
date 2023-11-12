/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:53:46 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/09 03:47:00 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

int	check_argerror(int ac, char **av, char *line)
{
	int	i;
	
	(void)ac;
	i = 0;
	while(av[i])
	{
		printf("Line: %s\n", line);
	}
	return (1);
}
/*
void	check_line(char *line)
{
	int	i;
	int	here_doc;

	i = 0;
	here_doc = 0;
	if (!heredoc)
		start = 0;
	while (line[i])
	i++;
	if (line[i] == '\0')
	{
		token = ft_substr(line, start, i);
	}

}
*/
