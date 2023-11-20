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
#include "../include/minishell.h"

/*@brief PWD, pendiente gestionar fallos en caso de error*/

void    get_pwd(void)
{
    size_t size = 1000;
    char *buffer;
    
    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        perror("Error en la asignación de memoria");
        return ;
    }
    char *result = getcwd(buffer, size);
    if (result == NULL) {
        perror("Error al obtener el directorio de trabajo actual");
        free(buffer);
        return ;
    }
    ft_putstr_fd(buffer, 1);
    free(buffer);
}
