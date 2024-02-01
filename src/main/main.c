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

volatile sig_atomic_t received_signal = 0;

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
	(*sack)->pipe_wc = 0;

	return (0);
}

int	sack_init(t_shell_sack *sack, char *line)
{
	sack->line = ft_strdup(line);
	if(!sack->line)
		return (free(line), 1);
	if (check_errors_initsack(sack))
		return (free(sack->line), 1);
	if (expand_line(sack))
		return (1);
	free (sack->line);
	if (sack->l_expanded == NULL)
		return (1);
	else if (sack->l_expanded[0] == '\0')
		return (free(sack->l_expanded), 1);
	sack->line = ft_strdup(sack->l_expanded);
	free (sack->l_expanded);
	sack->token_list = init_tokens(sack->line);
	get_cmd_args(&sack);
	return (0);
}



/*Una cosa a tener en cuenta es que si tienes los descriptores de archivos de entrada 
estándar redirigidos a un archivo no terminal, el comando de salida no debe ser impreso. 
Puede comprobar si un descriptor de archivos es un terminal o no utilizando 
la función isatty*/

int		minishell( char **envp)
{
	char 			*line;
	t_shell_sack	*sack;

	// atexit(leaks);
	sack = NULL;
	if (clean_init(&sack))
		return (1);
	if (env_init(sack, envp))
		return (1);
	sighandler();
	while (42)
 	{
		// main_sig_handler();
		sighandler();
 		line = readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			ft_clearenv(sack);
			exit (1);
		}
		if (line[0] == '\0')
			free(line);
		else if (*line)
		{
            add_history(line);
			// if (read_exit(line))
			// 	break;
			if (!sack_init(sack, line))
			{
 				free(line);
				init_tree(&sack);
				execute(&sack);
			}
			else
				free(line);
			// if (!ft_strncmp(line, "$EMPTY", 6))   
		}
		// if (received_signal != 0) 
        //     printf("Señal recibida: %d\n", received_signal);
		received_signal = 0;
		sack->old_pipes[0] = 0;
		sack->old_pipes[1] = 1;
		sack->new_pipes[0] = 0;
		sack->new_pipes[1] = 1;
	}
	// ft_clearenv(sack);
    return (0);
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!envp || !envp[0]) // Aquí se protege de env -i
		return (1);
    int exit_status = minishell(envp);
    exit(exit_status);
  return (0);
}