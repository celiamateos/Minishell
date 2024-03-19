/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <cmateos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:15:35 by cmateos-          #+#    #+#             */
/*   Updated: 2024/01/03 21:15:36 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "../../include/minishell.h"

// char *process_wildcard(t_shell_sack *sack, char *s)
// {
//     printf("\n%s", s);
//     return (ft_strdup("probando"));
// }


// /*
// @brief ALOCA MEMORIA. 
// @param old, i posicion donde se encuentra el wildcard a expandir
// @return linea expandidad, NULL en caso de error*/
// char *expand_wildcard(t_shell_sack *sack, char *old, int i)
// {
// 	(void)sack;
//     char *pre_expand = NULL;
// 	char *expand = NULL;
//     char *post_expand = NULL;
// 	char *temp;
// 	int start = 0;
// 	int len = i;
//     // printf("\nold[i]:%c", old[i]);
//     // printf("\nold:%s", old);
// 	if (sack == NULL)
// 		return NULL;
//     while (len > 0 && ft_isspace(old[len]) == 1)
// 	{

//         len--;
// 	}
// 	temp = ft_substr(old, 0, len);	
//     if (!temp)
//         return (NULL); 
//     // printf("\ntemp:%s\n", temp);
//     i = len;
//     while (old[len] != '\0' && !ft_isspace(old[len]))
//         len++;
//     expand = ft_substr(old, i, len);
//     if (!expand)
//         return (NULL);
//     // printf("\nexpand:%s\n", expand);
    
//     // if(old[i] == '*')
//         // printf("es *");
//     // if(old[i] == ' ')
//         // printf("es space");
    
//     // exit(1);
// 	len = 0;
// 	while (old[i] && !ft_isspace(old[i]) && old[i] != '\"' && old[i] != '\'')
// 	{
// 		len++;
// 		i++;
// 	}
// 	temp = ft_substr(old, start, len);
//     expand = process_wildcard(sack, temp);
// 	free (temp);
// 	if ((size_t)i < ft_strlen(old))
// 	{
// 		post_expand = ft_substr(old, i, ft_strlen(old));
// 	}
// 	if (pre_expand)
// 	{
// 		temp = ft_strjoin(pre_expand, expand);
// 		free (pre_expand);
// 		free(expand);
// 		expand = ft_strdup(temp);
// 		free (temp);
// 	}
// 	if (post_expand)
// 	{
// 		temp = ft_strjoin(expand, post_expand);
// 		free (expand);
// 		free (post_expand);
// 		expand = ft_strdup(temp);
// 		free (temp);
// 	}
// 	return (expand);
// }