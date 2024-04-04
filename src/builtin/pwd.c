/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 06:37:15 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/20 06:37:18 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_putpwd_fd(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write (1, &s[i], 1);
}

void	pwd_mserror(void)
{
	ft_putstr_fd("pwd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("\n", 2);
}

int	print_pwd(t_shell_sack *sack)
{
	if (!sack->env->pwd)
	{
		pwd_mserror();
		return (sack->last_exit);
	}
	ft_putpwd_fd(sack->env->pwd);
	ft_putstr_fd("\n", 1);
	return (0);
}
