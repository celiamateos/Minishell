/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "../../include/minishell.h"


// /*@brief Handle signals during heredoc execution creating file.
// Give some problems, get stuck on ^C*/
// void	heredoc_sig_handler(void)
// {
// 	struct sigaction	act_int;
// 	struct sigaction	act_quit;

// 	ft_bzero(&act_int, sizeof(act_int));
// 	act_int.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &act_int, NULL);
// 	ft_bzero(&act_quit, sizeof(act_quit));
// 	act_quit.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &act_quit, NULL);
// }

// /*@brief Manage signal Interrupt —usually the result of CTRL-C being hit.*/
// void	sigint_handler(int signum)
// {
// 	if (signum != SIGINT)
// 		return ;
// 	ft_putchar_fd('\n', 1);
// 	rl_replace_line("", 1); //en 42 esta linea no compila en WSL si. Habrá q instalar puto algo en 42 :)
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// /*@brief Manage signal Quit —the quit signal (SIGQUIT), which conventionally 
// tells the application to exit as soon as possible without saving anything; 
// many applications don't override the default behavior, which is to kill the 
// application immediately¹.*/
// void    main_sig_handler(void)
// {
// 	struct sigaction	act_int;
// 	struct sigaction	act_quit;

// 	ft_bzero(&act_int, sizeof(act_int));
// 	act_int.sa_handler = &sigint_handler;
// 	sigaction(SIGINT, &act_int, NULL);
// 	ft_bzero(&act_quit, sizeof(act_quit));
// 	act_quit.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &act_quit, NULL);
// }


void handle_sigint(int signal)
{
   	g_received_signal = signal;
    write(1, "\n", 1);  // Escribe un salto de línea
    rl_on_new_line();  // Reinicia la línea de entrada de la librería readline
    rl_replace_line("", 0);  // Reemplaza la línea actual con una cadena vacía
    rl_redisplay();  // Redisplay para reflejar los cambios
}


void sighandler(void)
{
    signal(SIGINT, &handle_sigint);  // Establece handle_sigint como el manejador para SIGINT
    signal(SIGQUIT, SIG_IGN);  // Ignora la señal SIGQUIT (Ctrl+\)
}


