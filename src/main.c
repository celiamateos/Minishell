/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:08:45 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/10 02:40:08 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "../include/minishell.h"

 int		main(int ac, char **av, char **envp)
 {
    (void)ac;
    (void)av;
    (void)envp;
    char *line;
	t_shell_sack	*sack;
	t_dlist			*tokens;

	tokens = NULL;
	sack = NULL;
//	clean_init(sack);
	while (42)
	{
		line =  readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
	//	init_sack(sack, line, sack->envp);
		if (line == 0)
			return (0);
		tokens = lexer(line);
/*		while (tokens->next)
		{
			print_next(tokens);
			tokens = tokens->next;
		}
*/
		free(line);
    }
    return (0);
 }
