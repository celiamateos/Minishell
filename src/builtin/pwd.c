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

/*@brief PWD, pendiente gestionar fallos en caso de error*/
int   get_pwd(void)
{
    size_t size = 1000;
    char *buffer;
    char *result;

    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        return (perror("Error en la asignación de memoria"), 1);
    }
    result = getcwd(buffer, size);
    if (result == NULL)
    {
        free(buffer);
        return (perror("Error al obtener el directorio de trabajo actual"), 1);
    }
    ft_putstr_fd(buffer, 1);
    ft_putstr_fd("\n", 1);
    free(buffer);
    return (0);
}
