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
# include "../../include/minishell.h"

void	ft_clearenv(t_shell_sack *sack)
{
    if (sack->env->pwd)
        free(sack->env->pwd);
    if (sack->env->oldpwd)
        free(sack->env->oldpwd);
    // if (sack->env->shlvl)
    free(sack->env->shlvl);
	ft_free_env(sack->env->pre_export);
	ft_free_env(sack->env->env);
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
        // if((*sack)->l_expanded)
        //     free((*sack)->l_expanded);
        // if((*sack)->cmd_rmquotes)
        //     free((*sack)->cmd_rmquotes);
        if ((*sack)->token_list)
            ft_dlstclear(&(*sack)->token_list, &free_token);
        if ((*sack)->tree_list)
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
        // if (&token->cmds)
        // if (*token->cmds)
            ft_freematrix(&token->cmds);
    }
    free(content);
}


void	ft_pustr_msjerror(int n, char *cmd)
{
	if (n == STANDAR)
		ft_putstr_fd(strerror(errno), 2);
	else if (n == COMANDNOTFOUND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
	else if (n == PERMISSIONDENIED)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
	else if (n == NOSUCHFILEORDIRECTORY)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd_noquotes(cmd, 2);
	}
    // else
    //     perror(cmd);
	ft_putstr_fd("\n", 2);
}

/*VERSION MEJORADA perror_free_exit*/
void free_exit(char **cmds, t_shell_sack ***sack, int msj)
{
    (void)cmds;
    (void)msj;
    int exitcode;
    char *cmd;

    cmd = ft_arrtostr(cmds);
    exitcode = (**sack)->last_exit;
    if (msj != 0)
        ft_pustr_msjerror(msj, cmd);
    ft_clearenv((**sack));
    free_sack(&(**sack));
    // printf("exitcode:%d\n", exitcode);
    exit(exitcode); //check error code for exit
}

/*@brief Used to return error message and free everything before exit*/
void	perror_free_exit(char *msj, t_shell_sack ***sack)
{
	perror(msj);
    int exitcode;

    exitcode = (**sack)->last_exit;

    // (**sack)->last_exit = 1; //Save it here for all fails?
    //print2D((**sack)->tree_list);
	// if ((**sack)->heredoc)
        // unlink("tmp/.heredoc");
    ft_clearenv((**sack));
    free_sack(&(**sack));
    // printf("exitcode:%d\n", exitcode);
    exit(exitcode); //check error code for exit
}

