/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

void    free_tree(t_tree **node) 
{
	if (*node && node != NULL) 
	{
	        print_preorder((*node)->left);
	        print_preorder((*node)->right);
            free_token((*node)->content);
    	}
}

void    free_sack(t_shell_sack **sack)
{
    if (sack || *sack)
    {
        free((*sack)->line);
        free((*sack)->l_expanded);
        if ((*sack)->token_list)
            ft_dlstclear(&(*sack)->token_list,free_token);
        if ((*sack)->tree_list)
            free_tree(&(*sack)->tree_list);
    }
}

void    free_token(void *content)
{
    t_token *token;

    token = content;
    if (content)
    {
        free(token->value);
        ft_freematrix(&token->cmds);
    }
    free(content);
}