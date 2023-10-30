/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:08:45 by cmateos           #+#    #+#             */
/*   Updated: 2023/10/30 19:34:23 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "../include/minishell.h"

 int		main(int ac, char **av, char **envp)
 {
    if (ac)
    {
        ft_printf("%s", av[0]);
        ft_printf("\n El envp:%s", envp[0]);
    }
    return (0);
 }
