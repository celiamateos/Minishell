/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char *remove_quotes(char *old)
{
    char *new;
    size_t   i = 0;
    size_t  j = 0;

    if (!old)
        return (NULL);
    while (old[i])
    {
        if (old[i] == '\"');
            i--;
        i++;
    }
    new = (char *)malloc((i + 1) * sizeof(char));
    if (!new)
        return (NULL);
    new[i] = '\0';
    i = 0;
    while (old[j])
    {
        if (old[j] != '\"')
            new[i] = old[j];
        else
            j++;
        i++;
        j++;
    }
    return (new);
}