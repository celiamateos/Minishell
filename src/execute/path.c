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
#include"../../include/minishell.h"
int	check_route(char *av)
{
	if (ft_strchr(av, '/'))
		return (1); //CON TO MI COÑO JEJE
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
	if (!env[i] || !env)
		return ("./");
	else
		paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd_path);
			return (ft_freematrix(&paths), path);
		}
		free(cmd_path);
		free(path);
		i++;
	}
	return (ft_freematrix(&paths), NULL);
}

// char	*getcmd_withpath(t_shell_sack *sack, char *cmd, char **cmds, char **env)
// {
// 	char	*aux;
// 	char 	*tmp;
// 	(void)cmds; // esto no se usa

// 	ft_print_strarray(cmds);

// 	// printf("\ndespues:");
// 	// exit(1);
// 	if ((ft_strchr(cmd, D_QUOTES) || ft_strchr(cmd, S_QUOTES)) && !check_open_quotes(NULL, cmd))
// 		sack->cmd_rmquotes = remove_quotes_cmd(cmd);
// 	else
// 		sack->cmd_rmquotes = ft_strdup(cmd);
// 	if (check_route(sack->cmd_rmquotes) == 1) // EXECUTE OTROS PROGRAMAS POR RUTA ABSOLUTA O RELATIVA.
// 		return (sack->cmd_rmquotes);
// 	else
// 	{
// 		aux = get_path(sack->cmd_rmquotes, env);
// 		if (aux)
// 		{
// 			tmp = ft_strjoin(aux, sack->cmd_rmquotes);
// 			free(sack->cmd_rmquotes);
// 			sack->cmd_rmquotes = ft_strdup(tmp);
// 			free(tmp);
// 			free(aux);
// 		}
// 	}
	
// }

char	*getcmd_withpath(char *cmd, char **cmds, char **env)
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