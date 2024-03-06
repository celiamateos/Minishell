
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:57:40 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/20 16:44:58 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(t_tree *root, int space)
{
	t_token	*token;
	int     i;

    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    ft_printf("\n");
    i = COUNT;
    while (i < space)
    {
        ft_printf(" ");
        i++;
    }
	token = root->content;
	printf("%s\n", token->value);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(t_tree* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void print_preorder(t_tree *node) 
{
	t_token	*token;

	if (node != NULL) 
	{
		token = node->content;
       		printf("%s\n", token->value);
	        print_preorder(node->left);
	        print_preorder(node->right);
    	}
}