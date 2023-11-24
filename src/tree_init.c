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
#include "../include/minishell.h"

void	leaf_isoper(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_tree	*leaf;
	t_token	*token;
	
	token = token_list->content;
	tree = *root;
	aux_leaf = *tree;
	leaf = new_leaf(token);
	leaf->left = aux_leaf;
	**root = leaf;
}

void	leaf_isredirect(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_tree	*leaf;
	t_token	*token;
	
	token = token_list->content;
	tree = *root;
	if ((*tree)->right == NULL)
		(*tree)->right = new_leaf(token);
	else
	{
		aux_leaf = *tree;
		while (aux_leaf->right)
			aux_leaf = aux_leaf->right;
		aux_leaf->right = new_leaf(token);
	}	
}

void	leaf_ispipe(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_tree	*leaf;
	t_token	*token;
	
	token = token_list->content;
	tree = *root;
	if ((*tree)->content->type == PIPE || (*tree)->content->type == OPER)
	{
		aux_leaf = *tree;
		while ((aux_leaf->right)->content->type == PIPE || (aux_leaf->right)->content->type == OPER)
			aux_leaf = aux_leaf->right;
		leaf = new_leaf(token);
		leaf->left = aux_leaf->right;
		aux_leaf->right = leaf;
	}
	else
	{
		leaf = new_leaf(token);
		aux_leaf = *tree;
		leaf->left = aux_leaf;
		*tree = leaf;
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
		if ((*tree)->right == NULL)
			(*tree)->right = new_leaf(token);
		else
		{
			aux_leaf = *tree;
			while ((aux_leaf->right)->right)
				aux_leaf = aux_leaf->right;
			if ((aux_leaf->right)->content->type >= HEREDOC)
			{
				leaf = new_leaf(token);
				if ((aux_leaf->right)->content->type <= REDIR_IN)
					leaf->left = aux_leaf->right;
				else
					leaf->right = aux_leaf->right;
				aux_leaf->right = leaf;
			}
			else
				(aux_leaf->right)->right = new_leaf(token);
		}
	}
}

t_tree	*new_leaf(t_token *token)
{
	t_tree	*leaf;

	leaf = malloc(sizeof(t_tree));
	if (!leaf)
		return (NULL);
	leaf->content = token;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}

void	insert_leaf(t_tree **tree, t_dlist **token_list, t_dlist *token_end)
{
	t_token	*token;
	t_tree	*leaf;
	t_tree	*aux_leaf;

	if (token_list == NULL || !*tree || !tree)
		return ;
	while ( (*token_list))
	{
		token = (*token_list)->content;
		if (token->type == CMD)
		{
			leaf_iscmd(&tree, (*token_list));
		}
		else if (token->type == PIPE)
		{
			leaf_ispipe(&tree, (*token_list));
		}
		else if (token->type >= HEREDOC)
		{
			leaf_isredirect(&tree, (*token_list));
		}
		else if (token->type == OPER)
		{
			leaf_isoper(&tree, (*token_list));
		}
		(*token_list) = (*token_list)->next;
	}
}

void	init_tree(t_shell_sack **sack)
{
	t_tree	*tree;
	t_token	*token;
	t_dlist	*token_to;
	t_dlist	*token_list;
	t_tree	*leaf;
	t_tree	*aux_leaf;

	token_list = (*sack)->token_list;
	token_to = token_list;
	// while (token_list)
	//  {
	// 	token = token_list->content;
	// 	if (token->type == OPER)
	// 	{
	// 		token_to = token_list;
	// 		break;
	// 	}
	// 	token_list = token_list->next;
	// }
	// token_list = (*sack)->token_list;
	// tree = new_leaf(token_list->content);
	// token_list = token_list->next;
	// insert_leaf(&tree, &token_list, token_to->next);
	
	tree = new_leaf(token_list->content);
	token_list = token_list->next;
	insert_leaf(&tree, &token_list, token_to->next); //erase token_to
	
//	insert_leaf(&tree, &token_list, token_to);
	
	
	
	// tree = new_leaf(token_list->content);
	// token_list = token_list->next;
	// insert_leaf(&tree, token_list);
	print2D(tree);
	//print_preorder(tree);
}
