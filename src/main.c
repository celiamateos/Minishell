/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:08:45 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/19 20:13:32 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "../include/minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

 int		main(int ac, char **av, char **envp)
 {
    (void)ac;
    (void)av;
    (void)envp;
	t_env		*env = NULL;
	char 		*line;
	t_shell_sack	*sack;
	t_dlist		*tokens;

	// atexit(leaks);
	 tokens = NULL;
	  sack = NULL;
	if (init_env(envp, env))
		return (1);
// 	clean_init(&sack);
// //	sack->env = env;
// 	while (42)
//  	{
//  		line =  readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
// //	 	init_sack(sack, line, sack->envp);
//  		if (line == 0)
//  			return (0);
// 		sack->token_list = lexer(line);
// 		print_tokenlist(sack->token_list);
// 		init_tree(&sack);
//  		free(line);
// 	}
	// 	ft_free_env(env->env);
	// // // ft_free_env(env->pre_export);
	// free(env);
    return (0);
 }
