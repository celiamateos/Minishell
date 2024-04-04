/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:51:44 by cmateos-          #+#    #+#             */
/*   Updated: 2024/04/02 14:51:45 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	insert_shlvlenv(t_shell_sack *sack, char *new)
{
	char	*aux;

	aux = ft_strjoin("SHLVL=", new);
	if (!aux)
		return (1);
	export(sack->env, aux);
	free (aux);
	return (0);
}

int	check_shlvl(int n, char *shlvl)
{
	n = ft_atoi(shlvl);
	if (n < 0)
		n = -1;
	else if (n >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level (1000) too high,"
			"resetting to 1\n", 2);
		n = 0;
	}
	return (n);
}

//Acortar esta función y revisar seguridad de mallocs
int	init_shlvl(t_shell_sack *sack)
{
	char	*shlvl;
	int		n;

	n = 1;
	shlvl = get_varname(sack, "SHLVL");
	if (shlvl)
	{
		n = check_shlvl(n, shlvl);
		free (shlvl);
		shlvl = ft_itoa(++n);
	}
	else
	{
		if (sack->env->shlvl)
			shlvl = sack->env->shlvl;
		else
			shlvl = ft_strdup("1");
	}
	if (!shlvl)
		return (1);
	insert_shlvlenv(sack, shlvl);
	sack->env->shlvl = ft_strdup(shlvl);
	free (shlvl);
	return (0);
}
