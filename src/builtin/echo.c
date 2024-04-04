/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:57:07 by cmateos-          #+#    #+#             */
/*   Updated: 2023/12/10 01:57:08 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	only_n(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
		i++;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] != 'n' && s[i] != '\"')
			return (1);
		i++;
	}
	return (0);
}

int	echo(char **arr_cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (arr_cmd[i] && only_n(arr_cmd[i]) == 0)
	{
		flag = 1;
		i++;
		while (only_n(arr_cmd[i]) == 0)
			i++;
	}
	if (arr_cmd[i])
	{
		ft_putstr_fd_noquotes(arr_cmd[i], 1);
		while (arr_cmd[++i] != NULL && arr_cmd[i][0] != '\0')
		{
			ft_putstr_fd_noquotes(" ", 1);
			ft_putstr_fd_noquotes(arr_cmd[i], 1);
		}
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
