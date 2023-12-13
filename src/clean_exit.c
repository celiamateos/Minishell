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

void	ft_clearenv(t_shell_sack *sack)
{
    if (sack->env->pwd)
        free(sack->env->pwd);
     if (sack->env->oldpwd)
        free(sack->env->oldpwd);
	ft_free_env(sack->env->env);
	ft_free_env(sack->env->pre_export);
	free(sack->env);
}

void    free_tree(t_tree **node) 
{
	if (*node != NULL && node != NULL) 
	{
	         free_tree(&(*node)->left);
	         free_tree(&(*node)->right);
            // printf("Token:\n\n\n");
            // printf("Token: %s\n", (*node)->content->value);
            // free_token((*node)->content);
            free(*node);
    	}
}

void    free_sack(t_shell_sack **sack)
{
    if (sack || *sack)
    {
        if((*sack)->line)
            free((*sack)->line);
        // if((*sack)->s_quotes)
        //     free((*sack)->s_quotes);
        // if((*sack)->d_quotes)
        //     free((*sack)->d_quotes);

        //print2D((*sack)->tree_list);
        if ((*sack)->token_list)
            ft_dlstclear(&(*sack)->token_list, &free_token);
        // if ((*sack)->env);
        //     ft_clearenv((*sack));
        // if ((*sack)->tree_list)
        free_tree(&(*sack)->tree_list);
    }
}

void    free_token(void *content)
{
    t_token *token;
    char    *value;

    token = content;
    value =  token->value;
    if (content)
    {
        if(value != NULL && token->value)
            free(token->value);
        if (&token->cmds)
            ft_freematrix(&token->cmds);
    }
    free(content);
}

void	ft_perror_exit(char *msj, t_shell_sack ***sack)
{
	perror(msj);
	if (sack)
        free_sack(&(**sack));
	exit(1); //check error code for exit
}