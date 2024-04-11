/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:57:40 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/20 16:44:58 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/* @brief Find in tree the next cmd token or parenthesis. Used to add
 operator flag, that in execution it will execute or not depends on exitcode*/
t_tree	*findright_cmd_redirleaf(t_tree **node)
{
	t_token	*token;
	t_tree	**aux_leaf;

	aux_leaf = node;
	token = (*aux_leaf)->content;
	if (token->type != CMD)
	{
		while ((*aux_leaf)->right != NULL)
		{
			if (((*aux_leaf)->right)->content->type == CMD)
				return ((*aux_leaf)->right);
			*aux_leaf = (*aux_leaf)->right;
		}
	}
	return (*aux_leaf);
}

int	leaf_isredirect_aux(t_tree **tree, t_dlist *token_list)
{
	t_tree	*aux_leaf;
	t_token	*token;

	token = token_list->content;
	aux_leaf = *tree;
	if (token->type >= REDIR_OUT && aux_leaf->right == NULL)
		aux_leaf->right = new_leaf(token);
	else if (token->type >= REDIR_OUT && aux_leaf->right->content->type >= REDIR_OUT)
	{
		while (aux_leaf->right)
			aux_leaf = aux_leaf->right;		
		aux_leaf->right = new_leaf(token);
	}
	else if (token->type >= HEREDOC && aux_leaf->left == NULL)
		aux_leaf->left = new_leaf(token);
	else if (token->type >= HEREDOC && aux_leaf->left->content->type >= HEREDOC)
	{
		while (aux_leaf->left)
			aux_leaf = aux_leaf->left;		
		aux_leaf->left = new_leaf(token);
	}
	else if ((aux_leaf->content->type >= PIPE && aux_leaf->content->type <= PARENT_CL) && aux_leaf->right == NULL)
		aux_leaf->right = new_leaf(token);
	else if (aux_leaf->content->type >= PIPE && aux_leaf->content->type <= PARENT_CL)
		return (0);
	return (1);
}

void	leaf_isredirect(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_token	*token;

	token = token_list->content;
	tree = *root;
	aux_leaf = *tree;

	if (!leaf_isredirect_aux(&aux_leaf, token_list))
	{
		aux_leaf = findright_cmd_redirleaf(&aux_leaf);
		leaf_isredirect_aux(&aux_leaf, token_list);
	}

}

void	auxleaf_iscmd(t_tree ****root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_tree	*leaf;

	tree = **root;
	if ((*tree)->right == NULL)
		(*tree)->right = new_leaf(token_list->content);
	else
	{
		aux_leaf = *tree;
		while ((aux_leaf->right)->right)
			aux_leaf = aux_leaf->right;
		if ((aux_leaf->right)->content->type >= HEREDOC)
		{
			leaf = new_leaf(token_list->content);
			if ((aux_leaf->right)->content->type <= REDIR_IN)
				leaf->left = aux_leaf->right;
			else
				leaf->right = aux_leaf->right;
			aux_leaf->right = leaf;
		}
		else
			(aux_leaf->right)->right = new_leaf(token_list->content);
	}
}

void	leaf_iscmd(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_token	*token;
	t_tree	*leaf;

	token = token_list->content;
	tree = *root;
	if ((*tree)->content->type >= HEREDOC)
	{
		leaf = new_leaf(token);
		aux_leaf = *tree;
		if ((*tree)->content->type <= REDIR_IN)
			leaf->left = aux_leaf;
		else
			leaf->right = aux_leaf;
		*tree = leaf;
	}
	else
	{
		auxleaf_iscmd(&root, token_list);
	}
}

void	insert_leaf(t_tree **tree, t_dlist **token_list)
{
	t_token	*token;

	if (token_list == NULL || !*tree || !tree)
		return ;
	while ((*token_list))
	{
		token = (*token_list)->content;
		if (token->type == CMD)
			leaf_iscmd(&tree, (*token_list));
		else if (token->type == PIPE || token->type == OPER)
			leaf_isoperpipe(&tree, (*token_list));
		else if (token->type >= HEREDOC)
			leaf_isredirect(&tree, (*token_list));
		else if (token->type == PARENT_OP)
			leaf_isparenthesis_op(&tree, (*token_list));
		else if (token->type == PARENT_CL)
			leaf_isparenthesis_cl(&tree, (*token_list));
		(*token_list) = (*token_list)->next;
	}
}

void	init_tree(t_shell_sack **sack)
{
	t_tree	*tree;
	t_dlist	*token_list;

	token_list = (*sack)->token_list;
	tree = new_leaf(token_list->content);
	token_list = token_list->next;
	insert_leaf(&tree, &token_list);
	(*sack)->tree_list = tree;
}
