/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:53:21 by cmateos           #+#    #+#             */
/*   Updated: 2024/04/04 17:53:22 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_clearenv(t_shell_sack *sack)
{
	if (sack->env->pwd)
		free(sack->env->pwd);
	if (sack->env->oldpwd)
		free(sack->env->oldpwd);
	free(sack->env->shlvl);
	ft_free_env(sack->env->pre_export);
	ft_free_env(sack->env->env);
	free(sack->env);
}

void	free_tree(t_tree **node)
{
	if (*node != NULL && node != NULL)
	{
		free_tree(&(*node)->left);
		free_tree(&(*node)->right);
		free(*node);
	}
}

void	free_sack(t_shell_sack **sack)
{
	if (sack || *sack)
	{
		if ((*sack)->line)
			free((*sack)->line);
		if ((*sack)->token_list)
			ft_dlstclear(&(*sack)->token_list, &free_token);
		if ((*sack)->tree_list)
			free_tree(&(*sack)->tree_list);
	}
}

void	free_token_noargs(void *content)
{
	t_token	*token;
	char	*value;

	token = content;
	value = token->value;
	if (content)
	{
		if (value != NULL && token->value)
			free(token->value);
	}
	free(content);
}
