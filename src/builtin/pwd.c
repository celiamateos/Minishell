/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 06:37:15 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/20 06:37:18 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
void    ft_putpwd_fd(char *s)
{
    int i;

    i = 3;
    while (s[++i])
    {
        write (1, &s[i], 1);
    }
}

void    pwd_mserror()
{
    ft_putstr_fd("pwd: ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd("\n", 2);
}

//EN ESTA FUNCION ANTES OBTENIA EL DIR ACUTAL CON getcwd()
//PERO BASH MUESTA EL DIR ACUTAL AUNQUE getcwd falle
int print_pwd(t_shell_sack *sack)
{
    if (!sack->env->pwd)
    {   
        pwd_mserror();
        return (sack->last_exit);
    }
    ft_putpwd_fd(sack->env->pwd);
    ft_putstr_fd("\n", 1);
    return (0);
}

// /*@brief PWD, pendiente gestionar fallos en caso de error*/
// int   get_pwd(void)
// {
//     size_t size = 1000;
//     char *buffer;
//     char *result;

//     buffer = (char *)malloc(size);
//     if (buffer == NULL) {
//         return (perror("Error en la asignación de memoria"), 1);
//     }
//     result = getcwd(buffer, size);
//     if (result == NULL)
//     {
//         free(buffer);
//         return (perror("Error al obtener el directorio de trabajo actual"), 1);
//     }
//     ft_putstr_fd(buffer, 1);
//     ft_putstr_fd("\n", 1);
//     free(buffer);
//     return (0);
// }
