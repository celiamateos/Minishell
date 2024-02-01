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
#include"../../include/minishell.h"

/* @brief When an operator is found on tree node, find next nearest command or
parenthesis at his right. Then change the value of the paremeter token->oper 
to respective operator.
@parameters This function receive the sack and current tree node. */
void    run_oper(t_tree *node)
{
    // t_shell_sack    **sack;
    t_token         *token;
    t_tree          *aux_node;


    // sack = *sack_orig;
    token = (node)->content;
    aux_node = findnext_cmdleaf(&node->right);
    if (aux_node != NULL) // maybe its not possible to get emtpy or should return error
    {
       	if (!ft_strncmp(token->value, "||", 3))
            aux_node->content->oper = OR;
       	else if (!ft_strncmp(token->value, "&&", 3))
            aux_node->content->oper = AND;
    }
}

/*@brief Creates new pipes and backup the old ones. 
Protect to not allow pipe in last node to not change std.
    (DAVID -I have tocheck thath)*/
void    run_pipe(t_shell_sack ***sack_orig, t_tree *node)
{
    (void)node;
     t_shell_sack    **sack;

    sack = *sack_orig;
    // if (node->content != (*sack)->last_token)
    // {
    (*sack)->old_pipes[0] = (*sack)->new_pipes[0];
    (*sack)->old_pipes[1] = (*sack)->new_pipes[1];
    // }
    if (pipe((*sack)->new_pipes) == -1)
		perror_free_exit("Pipe error", sack_orig);
    //  printf("Pipe oldpipes 0 %d 1 %d\n", (*sack)->old_pipes[0], (*sack)->old_pipes[1]);
    //  printf("Pipe new_pipes 0 %d 1 %d\n", (*sack)->new_pipes[0], (*sack)->new_pipes[1]);
    
}


void    run_cmd(t_shell_sack ***sack_orig, t_tree *node)
{
    t_token *token;
   	char	*cmd;
    t_shell_sack    **sack;

    sack = *sack_orig;
    token = node->content;
    (*sack)->last_exit = 0; //Esto lo he añadido recientemente
    (*sack)->last_pid = fork();
    if ((*sack)->last_pid < 0)
        perror_free_exit("Fork error", sack_orig);
    else if ((*sack)->last_pid == 0)
	{
        signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
        if(check_redirect(&sack, node))
        {
            (*sack)->last_exit = 1; //check error code
            perror_free_exit("Open error", sack_orig);
        }
        if ((*sack)->old_pipes[0] != 0 )
            if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1)
                perror_free_exit("Dup2 error IN", sack_orig);
        if ((*sack)->new_pipes[1] != 1 )
            if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
                perror_free_exit("Dup2 error OUT", sack_orig);
        ft_close((*sack)->new_pipes[0], (*sack)->new_pipes[1]);
        ft_close((*sack)->old_pipes[0], (*sack)->old_pipes[1]);
        if (!check_isbuiltin(node))
        {
            // printf("aki 1\n");
            execute_builtin(&sack, node);
            exit((*sack)->last_exit); //Aqui hay que salir porque si no el hijo no muere pero si el builtin se ingresa sin pipe, se debe ejecutar en el padre
        }
        else
        {
            remove_quotes_arr_cmds(token, &(*sack));
            cmd = getcmd_withpath(token->cmds[0], (*sack)->env->env);// change for our env
            if (cmd)
            {
                execve(cmd, token->cmds, (*sack)->env->env);
                // free(cmd); // no entiendo por que si libero esto da double free wtf?
            }
            (*sack)->last_exit = 127; //error code for cmd not found / ESTO ESTÁ INCOMPLETO/
            free_exit(token->cmds, sack_orig, COMANDNOTFOUND); //Free everything?
        } 

		// ft_freematrix(&token->cmds);
    }

    ft_close((*sack)->old_pipes[0], (*sack)->new_pipes[1]);
    // (*sack)->last_exit = wait_exitcode((*sack)->last_pid); //Aqui llama a waitpid
    signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
    int exitcode = wait_exitcode((*sack)->last_pid); //Aqui llama a waitpid
    // if ((*sack)->last_exit == 0)
    (*sack)->last_exit = exitcode;
    // if (!ft_strncmp(node->content->cmds[0], "exit", ft_strlen(node->content->cmds[0])))
    //     cmd_exit(&sack, node->content->cmds);
    // printf("EXITCODE: %d\n", (*sack)->last_exit);
	//waitpid((*sack)->last_pid, NULL, 0);
    ft_cpypipes((*sack)->old_pipes, (*sack)->new_pipes);
    (*sack)->new_pipes[1]  = 1; //add on cpy pipes?
}

/* @brief Executes appropriate function depends on type of token on tree. */
void    run_node(t_shell_sack **sack, t_tree **node)
{
   	t_token	*token;

    //  printf("TKEN: %s OPER %d\n", (*node)->content->value, (*node)->content->oper);
    // printf("oldpipes 0 %d 1 %d\n", (*sack)->old_pipes[0], (*sack)->old_pipes[1]);
    // printf("new_pipes 0 %d 1 %d\n", (*sack)->new_pipes[0], (*sack)->new_pipes[1]);
    token = (*node)->content;
    if (token->type == PARENT_CL)
    {
        if (!check_opercondition(sack, node))
            (*node)->right = NULL;
    }
    else if (token->type == CMD)
    {
        if (check_opercondition(sack, node) || (*node)->content->oper == 0)
        {

            run_cmd(&sack, (*node));
        }
    }
    else if (token->type == PIPE)
    {
        ++(*sack)->pipe_wc;
        run_pipe(&sack, (*node));
    }
    else if (token->type == OPER)
    {
        run_oper((*node));
    }
}

/* @brief Runs executor trough tree. This is the most common way but there's others.*/
void    run_preorder(t_tree *node, t_shell_sack **sack)
{

	if (node != NULL) 
	{	
        if (!check_isbuiltin(node) && (*sack)->pipe_wc == 0)
        {

                if(check_redirect(&sack, node))
                {
                    (*sack)->last_exit = 1; //check error code
                    printf("k koño");
                    perror_free_exit("Open error", &sack);
                }
                if ((*sack)->old_pipes[0] != 0 )
                    if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1)
                        perror_free_exit("Dup2 error IN", &sack);
                if ((*sack)->new_pipes[1] != 1 )
                    if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
                        perror_free_exit("Dup2 error OUT", &sack);
                ft_close((*sack)->new_pipes[0], (*sack)->new_pipes[1]);
                ft_close((*sack)->old_pipes[0], (*sack)->old_pipes[1]);
                (*sack)->last_exit = execute_builtin(&sack, node);
                // return ;
        }
        else
            run_node(sack, &node);
        run_preorder(node->left, sack);
        run_preorder(node->right, sack);
    }
}

void	execute(t_shell_sack **sack)
{
    // t_token *token;
    t_tree  *tree;

    tree = (*sack)->tree_list;
    // token = tree->content;
    // if (ft_strnstr((*sack)->line, "exit", 4))
    //     (*sack)->last_exit = cmd_exit(&sack, tree->content->cmds); 
    // else
        run_preorder(tree, sack);
    free_sack(&(*sack));
}

