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
