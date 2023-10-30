/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:09:14 by cmateos           #+#    #+#             */
/*   Updated: 2023/10/30 18:09:29 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h> //??
# include <stdlib.h> // Malloc, free
# include <fcntl.h>
# include <stdarg.h> // va_arg, etc.
# include <limits.h> 
# include <sys/wait.h> // waitpid, pipex.
# include "./libft/libft.h" 
# include <errno.h> //Código de error

int		main(int argc, char **argv, char **envp);

#endif
