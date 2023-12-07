/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

int	clean_init(t_shell_sack **sack)
{
	// check to use memset to initialize in one line
	*sack = (t_shell_sack *)malloc(sizeof(t_shell_sack));
	if (!*sack)
		return (1);
	(*sack)->line = NULL;
	(*sack)->l_expanded = NULL;
	(*sack)->token_list = NULL;
	(*sack)->tree_list = NULL;
	(*sack)->last_exit = 0;
	(*sack)->history_fd = -1;
	(*sack)->old_pipes[0] = 0;
	(*sack)->old_pipes[1] = 1;
	(*sack)->new_pipes[0] = 0;
	(*sack)->new_pipes[1] = 1;
	(*sack)->env = NULL;
	(*sack)->d_quotes = 0;
	(*sack)->s_quotes = 0;
	return (0);
}

// char	*get_varname(char *expanded, int i)
// {
// 	int		len;

// 	if (!expanded[i])
// 		return("");
// 	if (expanded[i] == '$')
// 		return ("$");
// 	len = (int)(ft_strchr(&expanded[i], ' ') - expanded[i]);
// 	if (len > ((int)ft_strchr(&expanded[i], '\'') - (int)expanded[i]))
// 		len = ((int)ft_strchr(&expanded[i], '\'') - (int)expanded[i]);
// 	return (ft_substr(expanded, i, (size_t)len));
// }

// char	*expand_var(char *line, int i, char **envp)
// {
// 	char	*var_name;
// 	char	*tmp;
// 	char	*extract;
// 	char	*str_prevar;

// 	(void)envp;
// 	var_name = get_varname(line, i + 1);
// 	str_prevar = ft_substr(line, 0, (size_t)i);
// 	tmp = str_prevar;
// 	if (line[i + 1] == '$')
// 		str_prevar = ft_strjoin(tmp, "No process ID from minishell");
// /*	else
// 		str_prevar = ft_strjoin(tmp, get_from_env(envp, var_name));
// */	free(tmp);
// 	tmp = str_prevar;
// 	extract = ft_substr(line, i, INT_MAX);
// 	str_prevar = ft_strjoin(tmp, extract);
// 	free(tmp);
// 	free(extract);
// 	free(line);
// 	free(var_name);
// 	return(str_prevar);
// }

// char	*expand_line(char *line, char **envp)
// {
// 	int	i;
// 	int	s_quote;
// 	char *expanded;

// 	i = 0;
// 	s_quote = 0;
// 	expanded = ft_strdup(line);
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 			s_quote = !s_quote;
// 		if (line[i] == '$' && s_quote == 0)
// 			expanded = expand_var(expanded, i, envp);
// 		i++;
// 	}
// 	return (expanded);
// }



int check_errors_initsack(t_shell_sack *sack)
{
	char *s;
	
	s = sack->line;
	check_open_quotes(sack, s);
	if (sack->d_quotes != 0 || sack->s_quotes != 0)
	{
		sack->d_quotes = 0;
		sack->s_quotes = 0;
		ft_putstr_fd("Input invalid, found open quotes\n", 2);
		return (1);
	}

	// if (d_quotes != 0)
	// 	printf("Error, OPEN D_QUOTES\n");
	// if (s_quotes != 0)
	// 	printf("Error, OPEN S_QUOTES\n");
	return (0);
}

char **realloc_split_line(t_shell_sack *sack, char **arr, int i)
{
	int pos;
	char *temp;

	temp = ft_substr(arr[i], 1, ft_strlen(arr[i]));
	// i += 1;
	pos = search_env_pos(sack->env->env, temp, '\0'); // aqui me kedaooo, no puedo mas..........
	printf("pos: %d\n", pos);

	return (NULL);
}


int	expand_line(t_shell_sack *sack)
{
	int i;
	char **split_line;
	// primero buscar si hay comillas y si no hay 
	//hacer substring directamente a l_exxpanded 
	//y despues ya expandir echo.
	if (ft_strchr(sack->line, '\"') || ft_strchr(sack->line, '\''))
	{
		expand_quotes(sack);
		printf("sack->l_expanded QUOTES: %s\n", sack->l_expanded);
	}
	else
		sack->l_expanded = sack->line;
	split_line = ft_split(sack->l_expanded, ' ');	
	if (!split_line)
		return (1); //Gestion de errores?
	i = 0;
	while (split_line[i])
	{
		if (split_line[i][0] == '$')
		{
			printf("AKIII");
			split_line = realloc_split_line(sack, split_line, i);
			if (!split_line)
				return (1); //LIBERAR ???
		}
		i++;
	}
	// free(sack->line);
	sack->line = ft_strdup(sack->l_expanded);
	if (!sack->line)
		return (1); //Proteger de errores ?
	free (sack->l_expanded);
}

int	sack_init(t_shell_sack *sack, char *line, char **envp)
{
	sack->line = ft_strtrim(line, " \t\v\n\r");
	if (check_errors_initsack(sack))
		return (1); //no se si aqui hay q liberar yo creo q si
	printf("sack line antes: %s\n", sack->line);
	if (expand_line(sack))
		return (1); //liberar ??
	printf("sack->l_expanded: %s\n", sack->line);
	sack->token_list = init_tokens(line); // enviar linea expandida y verificada de errores
	get_cmd_args(&sack);
	sack->last_token = get_last_cmd(&sack->token_list);
	//print_token("Last cmd", sack->last_token);
	//sack->last_token = get_last_cmd(&sack->token_list);
	//print_token_args(sack->token_list);
	return (0);
}

