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
# include "../../include/minishell.h"



int	sack_init(t_shell_sack *sack, char *line)
{
	//free(sack->line);
	// print_env(sack->env->env);
	sack->line = ft_strtrim(line, " \t\v\n\r");
	if (check_errors_initsack(sack))
		return (1); //no se si aqui hay q liberar yo creo q si
	// printf("sack line antes: %s\n", sack->line);
	if (expand_line(sack))
		return (1); //liberar ??
	// if (expand_quotes(sack))
	// 	return (1);
	// printf("sack->l_expanded:%s\n", sack->l_expanded);
	// free (line);
	if (sack->l_expanded == NULL || sack->l_expanded[0] == '\0')
		return (free(sack->l_expanded), 1);
	// line = ft_strdup(sack->l_expanded);
	free (sack->line);
	sack->line = ft_strdup(sack->l_expanded);
	free (sack->l_expanded);
	sack->token_list = init_tokens(sack->line); // enviar linea expandida y verificada de errores
	get_cmd_args(&sack);
	//sack->last_token = get_last_cmd(&sack->token_list); //check if is needed
	//print_token("Last cmd", sack->last_token);
	//sack->last_token = get_last_cmd(&sack->token_list);
	//print_token_args(sack->token_list);
	// free(line); // Creo que para borrarla hay que enviarla con & desde el main	
	return (0);
}

