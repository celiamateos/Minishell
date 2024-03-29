/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	check_route(char *av)
{
	if (ft_strchr(av, '/'))
		return (1);
	if (ft_strncmp(av, "/", 1) == 0 || ft_strncmp(av, "./", 2) == 0)
		return (1);
	else if (ft_strncmp(av, "../", 3) == 0)
		return (1);
	else
		return (0);
}

int	check_path(char **env)
{
	int	i;
	int	exist;

	exist = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			exist = 1;
		i++;
	}
	if (!exist)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*cmd_path;

	i = check_path(env);
	if (i == -1)
		return (NULL);
	if (!env[i] || !env)
		return ("./");
	else
		paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (free(cmd_path), ft_freematrix(&paths), path);
		free(cmd_path);
		free(path);
	}
	return (ft_freematrix(&paths), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*path2;
	char	**posibles_path;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	posibles_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (posibles_path[++i])
	{
		path2 = ft_strjoin(posibles_path[i], "/");
		path = ft_strjoin(path2, cmd);
		free (path2);
		if (access(path, F_OK) == 0)
			return (ft_free_env(posibles_path), path);
		free(path);
	}
	ft_free_env(posibles_path);
	return (NULL);
}

char	*getcmd_withpath(char *cmd, char **env)
{
	char	*path_cmd;
	char	*aux;

	path_cmd = NULL;
	if (check_route(cmd) == 1)
		path_cmd = cmd;
	else
	{
		aux = get_path(cmd, env);
		if (aux)
		{
			path_cmd = ft_strjoin(aux, cmd);
			free(aux);
		}
	}
	return (path_cmd);
}
