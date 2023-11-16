/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:36:49 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/12 03:37:12 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

//@brief ALOCA MEMORIA!
//Realloca el array env, omitiendo la línea que se desea eliminar.
//Retorna NULL en caso de fallo en la reserva de memoria, liberando lo alocado previamente en esta función.
char **realloc_unset(t_env *env, size_t pos)
{
    char **temp;
    size_t i;
    size_t j;

    if(!env)
        return (NULL);
    i = -1;
    j = 0;
    temp = (char **)malloc(env->env_elements * sizeof(char *));
    if (!temp)
        return(ft_free_env(env->env), NULL);
    while (++i < env->env_elements - 1)
    {
       if (i == pos)
            j++;
        temp[i] = ft_substr(env->env[j], 0, ft_strlen(env->env[j]));
        if (!temp[i])
            return(ft_free_error_arr(temp, i), ft_free_env(env->env), NULL);
        j++;
    }
    temp[i] = NULL;
    env->env_elements -= 1;
    ft_free_env(env->env);
    return (temp);
}

/*@brief ALOCA MEMORIA!
Realloca el array pre_export, omitiendo la línea que se desea eliminar.
@return NULL en caso de fallo en la reserva de memoria, liberando lo alocado previamente en esta función.
*/
char **realloc_unset_pre_export_list(t_env *env, size_t pos)
{
    char **temp;
    size_t i;
    size_t j;

    if(!env)
        return (NULL);
    i = -1;
    j = 0;
    temp = (char **)malloc(env->pre_export_elements * sizeof(char *));
    if (!temp)
        return(ft_free_env(env->pre_export), NULL);
    while (++i < env->pre_export_elements - 1)
    {
       if (i == pos)
            j++;
        temp[i] = ft_substr(env->pre_export[j], 0, ft_strlen(env->pre_export[j]));
        if (!temp[i])
            return(ft_free_error_arr(temp, i), ft_free_env(env->pre_export), NULL);
        j++;
    }
    temp[i] = NULL;
    env->pre_export_elements -= 1;
    ft_free_env(env->pre_export);
    return (temp);
}

/*
@brief Revisa si la posicion de la linea que quieres borrar existe. 
Retorna 1 en caso de fallo en alguna reserva de memoria.  
Habría que liberar env struct si esta funcion retorna 1. 
@param del La linea a borrar
@return 1 en caso de error, 0 si todo ok
@param check es un indicador para saber si hay que hacer unset en char **env (1) o en char **pre_export (0) o en ambas (2);
Esto es util porque al usar el comando unset a secas, elimina la variable de las 2 listas,
pero se puede reutilizar esta funcion para el uso de: VARIABLE="hola"; export VARIABLE;
VARIABLE se añade primero a pre_export, despues se mueve de pre_export a env y se elimina de pre_export. */
int unset(t_env *env, char *del, int check)
{
	long pos;

    if (env->env && (check == 2 || check == 1))
    {
        pos = search_env_pos(env->env, del, '\0');
	    if (pos >= 0)
        {
            env->env = realloc_unset(env, pos);
            if (!env->env)
                return (1);
        }
    }
    if (env->pre_export && (check == 2 || check == 0))
    {
        pos = search_env_pos(env->pre_export, del, '\0');
	    if (pos >= 0)
        {
            env->pre_export = realloc_unset_pre_export_list(env, pos);
            if (!env->pre_export)
                return (1);
        }
    }
    return (0);
}