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

void    run_pipe(t_shell_sack ***sack_orig, t_tree *node)
{
     t_shell_sack    **sack;

    sack = *sack_orig;
    if (node->content != (*sack)->last_token)
    {
        (*sack)->old_pipes[0] = (*sack)->new_pipes[0];
        (*sack)->old_pipes[1] = (*sack)->new_pipes[1];
    }
    if (pipe((*sack)->new_pipes) == -1)
		ft_perror_exit("Pipe error");
         printf("Pipe oldpipes 0 %d 1 %d\n", (*sack)->old_pipes[0], (*sack)->old_pipes[1]);
         printf("Pipe new_pipes 0 %d 1 %d\n", (*sack)->new_pipes[0], (*sack)->new_pipes[1]);
    
}

void    run_cmd(t_shell_sack ***sack_orig, t_tree *node)
{
    t_token *token;
   	char	*cmd;
    t_shell_sack    **sack;

    sack = *sack_orig;
    token = node->content;
   // if (node->content == get_last_cmd(&(*sack)->token_list))

    check_redirect(&sack, node);
    (*sack)->last_pid = fork();
    if ((*sack)->last_pid < 0)
        ft_perror_exit("Fork error");
    else if ((*sack)->last_pid == 0)
	{
//        check_isbuiltin(sack, node);
		cmd = getcmd_withpath(token->cmds[0], token->cmds, (*sack)->env->env);// change for our env
		// if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1
		// 	|| dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
		// 	ft_perror_exit("Dup2 error");
        if ((*sack)->old_pipes[0] != 0 )
            if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1)
                ft_perror_exit("Dup2 error IN");
        else
            if (dup2(0, STDIN_FILENO) == -1)
                ft_perror_exit("Dup2 error IN");

        if (node->content != (*sack)->last_token)
        {
            close((*sack)->new_pipes[0]);
            if ((*sack)->new_pipes[1] != 1 )
                if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
                    ft_perror_exit("Dup2 error OUT");
            else
                if (dup2(1, STDOUT_FILENO) == -1)
                    ft_perror_exit("Dup2 error OUT");
        }
        // close((*sack)->new_pipes[0]);
        //     if ((*sack)->new_pipes[1] != 1 )
        //         if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
        //             ft_perror_exit("Dup2 error OUT");
        //     else
        //         if (dup2(1, STDOUT_FILENO) == -1)
        //             ft_perror_exit("Dup2 error OUT");

        ft_close((*sack)->new_pipes[0], (*sack)->new_pipes[1]);
	    close((*sack)->old_pipes[0]);
		execve(cmd, token->cmds, (*sack)->env->env);// change for our env
		ft_perror_exit(cmd);
    }
    ft_close((*sack)->old_pipes[0], (*sack)->new_pipes[1]);
	waitpid((*sack)->last_pid, NULL, 0);
    if (node->content != (*sack)->last_token)
        ft_cpypipes((*sack)->old_pipes, (*sack)->new_pipes);
}

void    run_node(t_shell_sack **sack, t_tree *node)
{
   	t_token	*token;

    printf("oldpipes 0 %d 1 %d\n", (*sack)->old_pipes[0], (*sack)->old_pipes[1]);
    printf("new_pipes 0 %d 1 %d\n", (*sack)->new_pipes[0], (*sack)->new_pipes[1]);
    token = node->content;
    if (token->type >= HEREDOC)
    {
        // check_redirect(node);
        // open_redirect(node);
        // Do nothing?
    }
    else if (token->type == CMD)
    {
        run_cmd(&sack, node);
    }
    else if (token->type == PIPE)
    {
        run_pipe(&sack, node);
    }
}

void    run_preorder(t_tree *node, t_shell_sack **sack)
{
	if (node != NULL) 
	{	
         printf("TKEN: %s\n", node->content->value);
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

