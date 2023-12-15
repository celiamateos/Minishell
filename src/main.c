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

//Mete lo que quieras aquí para liberar si todo ha ido bien al final del main
void	ft_free_pruebas(t_shell_sack **sack)
{
	free_sack(&(*sack));
	ft_free_env((*sack)->env->env);
	ft_free_env((*sack)->env->pre_export);
	free((*sack)->env);
}

 int		main(int ac, char **av, char **envp)
 {
    (void)ac;
    (void)av;
    (void)envp;
	t_env		*env;
	char 		*line;
	t_shell_sack	*sack;

	atexit(leaks);
	sack = NULL;
	env = ft_calloc(1, sizeof(t_env));
	if (init_env(envp, env))
		return (1);
	clean_init(&sack);
	sack->env = env;
	while (42)
 	{
 		line = readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
	 	if (line == 0)
 			return (0);
		if (*line && !check_emptyorspace(line))
		{
			if (!sack_init(sack, line))
			{
				init_tree(&sack);
				execute(&sack);
				// print2D(sack->tree_list);
			}
			//print_tokenlist(sack->token_list);
			free_sack(&sack);
			// print2D(sack->tree_list);
			//print_preorder(sack->tree_list);
		}
		if (*line)
            add_history(line);
 		free(line);
		//reset sack and free tokens and list?
	sack->old_pipes[0] = 0;
	sack->old_pipes[1] = 1;
	sack->new_pipes[0] = 0;
	sack->new_pipes[1] = 1;
	}
	ft_free_pruebas(&sack);
    return (0);
 }
