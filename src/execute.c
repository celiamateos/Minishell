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



void    check_redirect(t_shell_sack **sack, t_tree *node)
{
    open_redirect(node);
}
void    run_pipe(t_shell_sack **sack, t_tree *node)
{
    if ((*sack)->new_pipe)
    {
        (*sack)->old_pipe[0] = (*sack)->new_pipe[0];
	    (*sack)->old_pipe[1] = (*sack)->new_pipe[1];
    }
    if (pipe((*sack)->new_pipe) == -1)
		ft_perror_exit("Pipe error");
    
}

void    run_cmd(t_shell_sack **sack, t_tree *node)
{
    (*sack)->last_pid = fork();
    if ((*sack)->last_pid < 0)
        ft_perror_exit("Fork error");
    else if ((*sack)->last_pid == 0)
	{
        check_redirect(node);
		cmd = getcmd_withpath(av, &cmds, env);
    /*if ((*sack)->redirs)
        dup2_redirect(sack);*/
        close((*sack)->new_pipe[0]);
		if (dup2(fd_in, STDIN_FILENO) == -1
			|| dup2(main_pipe[1], STDOUT_FILENO) == -1)
			ft_perror_exit("Dup2 error");
		close((*sack)->new_pipe[1]);
		//close(fd_in);
		execve(cmd, cmds, env);
		ft_perror_exit(cmds[0]);
    }
    if ((*sack)->old_pipes)
        ft_close(old_pipe[0], new_pipe[1]);
    else
    	close((*sack)->new_pipe[1]);
	waitpid((*sack)->last_pid, NULL, 0);
}

void    run_leaf(t_shell_sack **sack, t_tree *node)
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
        run_leaf(sack, node);
        run_preorder(node->left);
        run_preorder(node->right);
    }
}

void	exeute(t_shell_sack **sack)
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

