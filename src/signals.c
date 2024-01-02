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
#include"../include/minishell.h"

/*@brief Handle signals during heredoc execution creating file.
Give some problems, get stuck on ^C*/
void    heredoc_sig_handler(void)
{
    struct sigaction	act_int;
    struct sigaction	act_quit;

    ft_bzero(&act_int, sizeof(act_int));
    act_int.sa_handler = SIG_IGN;
    sigaction(SIGINT, &act_int, NULL);
    ft_bzero(&act_quit, sizeof(act_quit));
    act_quit.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &act_quit, NULL);
}

/*@brief Manage signal Interrupt —usually the result of CTRL-C being hit.*/
void    sigint_handler(int signum)
{
    (void)signum; //unused
    write(1, "\n", 1);
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
}

/*@brief Manage signal Quit —the quit signal (SIGQUIT), which conventionally 
tells the application to exit as soon as possible without saving anything; 
many applications don't override the default behavior, which is to kill the 
application immediately¹.*/
void    main_sig_handler(void)
{
    struct sigaction	act_int;
    struct sigaction	act_quit;

    ft_bzero(&act_int, sizeof(act_int));
    act_int.sa_handler = &sigint_handler;
    sigaction(SIGINT, &act_int, NULL);
    ft_bzero(&act_quit, sizeof(act_quit));
    act_quit.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &act_quit, NULL);
}
