/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

/* @brief to take off lines on run_node. Check conditions of execution 
of operators.*/
int check_opercondition(t_shell_sack **sack, t_tree **node)
{
   	t_token	*token;

    token = (*node)->content;
    if (token->oper == AND && (*sack)->last_exit == 0)
    {
        //printf("Cumple &&");
        return (1);
    }
    else if (token->oper == OR && (*sack)->last_exit != 0)
    {
        //printf("Cumple ||");
        return (1);
    }
    else
        return (0);
}

/* @brief Find in tree the next cmd token or parenthesis. Used to add
 operator flag, that in execution it will execute or not depends on exitcode*/
t_tree *findnext_cmdleaf(t_tree **node)
{
    t_token *token;

    token = (*node)->content;
    if (token->type != CMD || token->type != PARENT_CL)
    {
        if ((*node)->left != NULL) 
            if (((*node)->left)->content->type == CMD || ((*node)->left)->content->type == PARENT_CL)
                return((*node)->left);
        if ((*node)->right != NULL) 
            if (((*node)->right)->content->type == CMD || ((*node)->right)->content->type == PARENT_CL)
                return((*node)->right);
    }
    return((*node));
}

/* @brief assign fd and open attreibutes deppends on redirection */
void    open_redirect(t_shell_sack ****sack_orig, t_tree *node)
{
    t_token *token;

    token = node->content;
    t_shell_sack **sack;

    sack = **sack_orig;
    if (token->type == HEREDOC)
        (*sack)->old_pipes[0] = open("tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
    else if (token->type == REDIR_IN)
        (*sack)->old_pipes[0] = open(token->value, O_RDONLY);
    else if (token->type == REDIR_OUT)
        (*sack)->new_pipes[1] = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    else if (token->type == APPEND_OUT)
        (*sack)->new_pipes[1] = open(token->value, O_RDWR | O_CREAT | O_APPEND, 0666);
    if ((*sack)->old_pipes[0] == -1 || (*sack)->new_pipes[1] == -1)
        {
            (*sack)->last_exit = 1; //check error code
            ft_perror_exit("Open error");
        }
}

/* @brief check if cmd has redirection, and if it has, calls open_redirect 
to assign fds*/
int    check_redirect(t_shell_sack ***sack_orig, t_tree *node)
{
    t_token         *token;
    t_shell_sack    **sack;
    int             i;

    
	if (node != NULL) 
	{	
        i = 0;
        sack = *sack_orig;
        token = node->content;
        if (node->left && node->left->content->type >= HEREDOC)
        {
            i = 1;
            open_redirect(&sack_orig, node->left);
        }
        if (node->right && node->right->content->type >= HEREDOC)
        {
            i = 1;
            open_redirect(&sack_orig, node->right);   
        }
        // printf("REDIRECT oldpipes 0 %d 1 %d\n", (*sack)->old_pipes[0], (*sack)->old_pipes[1]);
        // printf("REDIRECT new_pipes 0 %d 1 %d\n", (*sack)->new_pipes[0], (*sack)->new_pipes[1]);
    }
    return (i);
}

void	ft_cpypipes(int *old_pipe, int *new_pipe)
{
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
}

/* @brief Close fds sended as parameters. Has protection to not close STDs*/
void	ft_close(int fd1, int fd2)
{
    if (fd1 > 2) //To protect to close fds standard
	    close(fd1);
	if (fd2 > 2)
        close(fd2);
}