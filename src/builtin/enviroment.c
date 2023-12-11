/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:41:52 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/09 03:41:53 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
//@brief  ????? Recibe el envp, alloca memoria exacta para su copia.
//Si el envp no existe (env -i ./minishell), aloca
//un char** de size 2, uno para '\0' y otro para el NULL, hay que hacer eso?
char **alloc_first_envp(t_env *env, char **src)
{
	char **result = NULL;
	size_t i;

	env->env_elements = ft_arraylen(src);
	i = -1;
	if (src)
	{
		result = (char **)malloc((env->env_elements + 1) * sizeof(char *));
		if (!result)
			return (NULL);
		while (++i < env->env_elements)
		{
			result[i] = ft_strdup(src[i]);
			if (!result)
				return (NULL);
		}
	}
	else
	{
		result = (char **)malloc(2 * sizeof(char *)); //Aqui hay que crear un enviroment si no existiera envp, al menos con: shlvl, pwd, oldpwd, 
		if (!result)
			return (NULL);
		result[i + 1] = '\0';
		i += 2;
	}
	result[i] = NULL;
	return (result);
}

int	init_pwd(t_env *env)
{
	int pos;

	pos = search_env_pos(env->env, "PWD=", '=');
	if (pos >= 0)
	{
		env->pwd = ft_strdup(env->env[pos]);
		if (!env->pwd)
			return (1);
	}
	pos = search_env_pos(env->env, "OLDPWD=", '=');
	if (pos >= 0)
	{
		env->oldpwd = ft_strdup(env->env[pos]);
		if (!env->oldpwd)
			return (1);
	}
	return (0);
}


//@brief ALOCA MEMORIA char **env->env para hacer una copia del envp
//Liberar char **env->env y en main o salida de errores.
// FALTA INCREMENTAR SHLVL +1 cada vez que se ejecuta minishell. Si SHLVL ha sido eliminado, al volver a correr bash o al hacer exit, shlvl=1 
// Gestionar error si SHVL es mayor de 1000 (creo) da el siguiente error:
// bash: warning: shell level (1000) too high, resetting to 1
//@return 1 en caso de error
int	init_env(char **envp, t_env *env)
{
	if (!env)
		return (1);
	if (envp)
	{
		// printf("\nENV ORIGINAL:\n");
		// print_env(envp);
		env->env = alloc_first_envp(env, envp);
		if (!env->env)
			return (1);
		env->pre_export_elements = 0;
		if (init_pwd(env))
			return (1);
		// print_env(env->env);
	}
	return (0);
}
