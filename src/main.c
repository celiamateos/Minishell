/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:08:45 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/08 22:31:36 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "../include/minishell.h"

void	print_next(t_token *tokens)
{
	if (!tokens->prev)
	{
		printf("content: %s next: %s\n", tokens->content, 
				(tokens->next)->content);
		tokens = tokens->next;
	}
	else if (tokens->next)
	{
		printf("content: %s next: %s prev: %s\n", tokens->content,
				(tokens->next)->content, (tokens->prev)->content);
		tokens = tokens->next;
	}
}

void	print_prev(t_token *tokens)
{
	if (!tokens->next)
	{
		printf("content: %s prev: %s\n", tokens->content, 
				(tokens->prev)->content);
		tokens = tokens->prev;
	}
	else if (tokens->prev)
	{
		printf("content: %s next: %s prev: %s\n", tokens->content,
				(tokens->next)->content, (tokens->prev)->content);
		tokens = tokens->prev;
	}
}

void	leaks(void)
{
	system("leaks -q minishell");
}

 int		main(int ac, char **av, char **envp)
 {
    (void)ac;
    (void)av;
    (void)envp;
    // char *line;

	t_env	*env = NULL;
	// t_token	*tokens;
	// tokens = NULL;

	//atexit(leaks);
	if (init_env(envp, env))
		return (1);
	//tokens = init_tokens();
/*	while (tokens->next)
	{
		print_next(tokens);
		tokens = tokens->next;
	}
	while (tokens->prev)
	{
		print_prev(tokens);
		tokens = tokens->prev;
	}*/
//    while (42)
//     {
//     	line =  readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
     	
// 	tokens = init_tokens(line);
// 	while (tokens->next)
// 		while (tokens->next)
// 		{
// 			print_next(tokens);
// 			tokens = tokens->next;
// 		}
// 		while (tokens->prev)
// 		{
// 			print_prev(tokens);
// 			tokens = tokens->prev;
// 		}
// 		free(line);
//     }
    return (0);
 }
