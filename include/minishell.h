/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:09:14 by cmateos           #+#    #+#             */
/*   Updated: 2023/10/30 19:35:38 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h> 
# include <stdlib.h> 
# include <fcntl.h>
# include <stdarg.h> 
# include <limits.h> 
# include <sys/wait.h> 
# include "../libft/libft.h" 
# include <errno.h> 

int		main(int ac, char **av, char **envp);

#endif
