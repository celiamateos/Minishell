/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

void    run_pipe(t_shell_sack **sack, t_tree *node)
{
    if ((*sack)->new_pipes)
    {
        (*sack)->old_pipes[0] = (*sack)->new_pipes[0];
	    (*sack)->old_pipes[1] = (*sack)->new_pipes[1];
    }
    if (pipe((*sack)->new_pipes) == -1)
		ft_perror_exit("Pipe error");
    
}

void    run_cmd(t_shell_sack **sack, t_tree *node)
{
    t_token *token;
   	char	*cmd;

    token = node->content;
   // if (node->content == get_last_cmd(&(*sack)->token_list))

        check_redirect(&sack, node);
    (*sack)->last_pid = fork();
    if ((*sack)->last_pid < 0)
        ft_perror_exit("Fork error");
    else if ((*sack)->last_pid == 0)
	{
        printf("oldpipes 0 %d 1 %d\n", (*sack)->old_pipes[0], (*sack)->old_pipes[1]);
//        check_isbuiltin(sack, node);
		cmd = getcmd_withpath(token->cmds[0], token->cmds, (*sack)->env->env);// change for our env
		// if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1
		// 	|| dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
		// 	ft_perror_exit("Dup2 error");
        if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1)
            ft_perror_exit("Dup2 error IN");
        if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
            ft_perror_exit("Dup2 error OUT");
        ft_close((*sack)->new_pipes[0], (*sack)->new_pipes[1]);
	    ft_close((*sack)->old_pipes[0], (*sack)->old_pipes[1]);
        // close((*sack)->new_pipes[0]);
		// close((*sack)->new_pipes[1]);
		//close(fd_in);
		execve(cmd, token->cmds, (*sack)->env->env);// change for our env
		ft_perror_exit(cmd);
    }
    if ((*sack)->old_pipes)
        ft_close((*sack)->old_pipes[0], (*sack)->new_pipes[1]);
    else
    	close((*sack)->new_pipes[1]);
	waitpid((*sack)->last_pid, NULL, 0);
}

void    run_node(t_shell_sack **sack, t_tree *node)
{
   	t_token	*token;

    token = node->content;
    if (token->type >= HEREDOC)
    {
        // check_redirect(node);
        // open_redirect(node);
        // Do nothing?
    }
    else if (token->type == CMD)
    {
        run_cmd(sack, node);
    }
    else if (token->type == PIPE)
    {
        run_pipe(sack, node);
    }
}

void    run_preorder(t_tree *node, t_shell_sack **sack)
{
	if (node != NULL) 
	{	
        run_node(sack, node);
        run_preorder(node->left, sack);
        run_preorder(node->right, sack);
    }
}

void	execute(t_shell_sack **sack)
{
    t_token *token;
    t_tree  *tree;

    tree = (*sack)->tree_list;
    run_preorder(tree, sack);
    /*while (tree)
    {
        token = tree->content->value;
        run_preorder(tree);
    }*/
	
}

