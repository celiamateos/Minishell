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
#include "../../include/minishell.h"
void	leaks(void)
{
	system("leaks -q minishell");
}

int	clean_init(t_shell_sack **sack)
{
	// check to use memset to initialize in one line
	*sack = (t_shell_sack *)malloc(sizeof(t_shell_sack));
	if (!*sack)
		return (1);
	(*sack)->line = NULL;
	(*sack)->l_expanded = NULL;
	(*sack)->is_string = 0;
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

int		main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
	t_env		*env;
	char 		*line;
	t_shell_sack	*sack;

	// atexit(leaks);
	sack = NULL;
	env = ft_calloc(1, sizeof(t_env));
	if (init_env(envp, env))
		return (1);
	clean_init(&sack);
	sack->env = env;
	while (42)
 	{
		// main_sig_handler();
 		line = readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
	 	if (line == 0)
 			return (0);
		if (*line && !check_emptyorspace(line))
		{
            add_history(line);
			if (read_exit(line))
				break;
			if (!sack_init(sack, line))
			{
				init_tree(&sack);
				// print_tokenlist(sack->token_list);
				execute(&sack);
				// print2D(sack->tree_list);
			}
			// free_sack(&sack);
			// print2D(sack->tree_list);
			//print_preorder(sack->tree_list);
		}
		// if (*sack->line)
        //     add_history(sack->line);
 		free(line);
		// free(sack->line);
		//reset sack and free tokens and list?
		sack->old_pipes[0] = 0;
		sack->old_pipes[1] = 1;
		sack->new_pipes[0] = 0;
		sack->new_pipes[1] = 1;
	}
	ft_clearenv(sack);
    return (0);
}
