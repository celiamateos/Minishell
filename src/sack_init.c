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
	(*sack)->pos = 0;
	(*sack)->token_list = NULL;
	(*sack)->tree_list = NULL;
	(*sack)->last_exit = 0;
	(*sack)->history_fd = -1;
	(*sack)->heredoc = 0;
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

void check_open_quotes(t_shell_sack *sack, char *s)
{
	int i;
	
	i = -1;
	if (!s || s[i + 1] == '\0')
		return ; //No se si hay que proteger aqui.
	while (s[++i])
	{
		if (s[i] == '\"')
		{
			sack->d_quotes = !sack->d_quotes;
			if (!search_char(s, '\"', i + 1))
				break ;
			i = search_char(s, '\"', i + 1);
			sack->d_quotes = !sack->d_quotes;
		}
		else if (s[i] == '\'')
		{
			sack->s_quotes = !sack->s_quotes;
			if (!search_char(s, '\'', i + 1))
				break ;
			i = search_char(s, '\'', i + 1);
			sack->s_quotes = !sack->s_quotes;
		}
	}
}

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

int	expand_line(t_shell_sack *sack)
{


	if (expand_quotes(sack))
		return(1);
	if (expand_dolar(sack))
		return (1);


	// sack->line = ft_strdup(sack->l_expanded);
	// if (!sack->line)
	// 	return (1); //Proteger de errores ?
	// free (sack->l_expanded);
	return (0);
}

int	sack_init(t_shell_sack *sack, char *line)
{
	//free(sack->line);
	sack->line = ft_strtrim(line, " \t\v\n\r");
	if (check_errors_initsack(sack))
		return (1); //no se si aqui hay q liberar yo creo q si
	// printf("sack line antes: %s\n", sack->line);
	if (expand_line(sack))
		return (1); //liberar ??
	//printf("sack->l_expanded:%s\n", sack->l_expanded);
	// free (line);
	line = ft_strdup(sack->l_expanded);
	// line = ft_substr(sack->l_expanded, 0, ft_strlen(sack->l_expanded));
		// return (1);
	// line = sack->l_expanded;
	free (sack->l_expanded);
	sack->token_list = init_tokens(line); // enviar linea expandida y verificada de errores
	get_cmd_args(&sack);
	//sack->last_token = get_last_cmd(&sack->token_list); //check if is needed
	//print_token("Last cmd", sack->last_token);
	//sack->last_token = get_last_cmd(&sack->token_list);
	//print_token_args(sack->token_list);
	free(line); // Creo que para borrarla hay que enviarla con & desde el main
	return (0);
}

