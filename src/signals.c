/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

/*@brief Manage signal oc ctrl + c*/
void    sigint_handler(int signum)
{
    signal(SIGINT, SIG_IGN);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        // sigint_handler(signum);
        write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
    else if (signum == (SIGQUIT))
    	signal(SIGQUIT, SIG_IGN);

}
