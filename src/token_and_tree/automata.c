/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// automata.c
int	idx(char *alphabet[], char c)
{
	int	i;

	i = -1;
	while (alphabet[++i])
		if (alphabet[i][0] == c)
			break ;
	if (i == 4)
		i = 3;
	else if (i == 9)
		i = 5;
	else if (i >= 5)
		i = 4;
	return (i);
}

int	evaluate(t_automata *a)
{
	t_token	*token;
	t_dlist	**token_list;
	char	type;

	a->i = -1;
	token_list = a->token_list;

	while (*token_list)
	{
		token = (*token_list)->content;
		type = token->type + '0';
		a->state = a->get_state(a->state, idx((a->alphabet), type));
		a->ostate = a->state;
		(*token_list) = (*token_list)->next;

	}
	// a->state = a->get_state(a->state, 5);
	return (a->state);
}

void	evaluate_file(t_automata *a, char *dir,
		void (*f)(t_automata *a, int state))
{
	int		file;
	char	*line;

	file = open(dir, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		a->str = line;
		a->state = 0;
		f(a, evaluate(a));
		free (line);
		line = get_next_line(file);
	}
	close(file);
}


// automata_init
/**
 * 	Alphabet definitions
**/
void	alphabet_init(t_automata *a)
{
	a->alphabet = ft_sarradd(a->alphabet, "0"); //CMD
	a->alphabet = ft_sarradd(a->alphabet, "1"); //PIPE
	a->alphabet = ft_sarradd(a->alphabet, "2"); //OPER
	a->alphabet = ft_sarradd(a->alphabet, "3"); //PARENT_OP
	a->alphabet = ft_sarradd(a->alphabet, "4"); //PARENT_CL
	a->alphabet = ft_sarradd(a->alphabet, "5"); //HEREDOC
	a->alphabet = ft_sarradd(a->alphabet, "6"); //REDIR_IN
	a->alphabet = ft_sarradd(a->alphabet, "7"); //REDIR_OUT
	a->alphabet = ft_sarradd(a->alphabet, "8"); //APPEND_OUT
}

int	get_state(int i, int j)
{
	const int states[][6] = {
//  CMD,|, &,(),<>,
	{9, 2, 2, 5, 1, 7},   // 0  Empty input (First input)
	{9, 2, 2, 1, 2, 1},   // 1  Redirs with no cmd
	{2, 2, 2, 2, 2, 2},   // 2  Oper syntax error
	{9, 2, 2, 5, 1, 2},   // 3  Pipe open
	{9, 2, 2, 5, 1, 2},   // 4  Oper (&& ||) open
	{9, 2, 2, 2, 1, 10},   // 5  Parentheses open
	{6, 6, 6, 6, 6, 6},   // 6 CMD syntax error
	{7, 7, 7, 7, 7, 7},   // 7 Invalid input
	{6, 3, 4, 8, 8, 10},   // 8  REDIRS open
	{6, 3, 4, 9, 8, 10},   // 9 CMD
	{10, 10, 10, 10, 10, 10},   // 10 Valid input
	};

	return (states[i][j]);
}

/**
 * 	Error strings to print when automata finish on a
 * 		non ending state.
**/
void	errors_init(t_automata *a)
{
	a->errors = NULL;
	a->errors = ft_sarradd(NULL, "Empty string.");
	a->errors = ft_sarradd(a->errors, "Redirections with no cmd");
	a->errors = ft_sarradd(a->errors, "Operator syntax error");
	a->errors = ft_sarradd(a->errors, "Operator syntax error near '|'");
	a->errors = ft_sarradd(a->errors, "Operator syntax error near '|| &&'");
	a->errors = ft_sarradd(a->errors, "Operator syntax error near '()'");
	a->errors = ft_sarradd(a->errors, "Command syntax error");
	a->errors = ft_sarradd(a->errors, "Invalid input");
	a->errorlen = ft_sarrlen(a->errors);
}

/**
 *	Simple actions, they trigger when entering a state.
**/
void	sactions_init(t_automata *a)
{
	(void)a;
}

void	print_error(char *msj)
{
	if (!msj || msj == NULL)
		printf("Validation token error: \n");
	else
		printf("Validation token error: %s\n", msj);
}

/**
 *	Transition actions, they trigger when going
 * 		from one state to another.
**/
void	tactions_init(t_automata *a)
{
	(void)a;
	// a->fta[0][CMD] = get_token;
	// a->fta[NOT_OPERATOR][LESS] = get_token;
	// a->fta[NOT_OPERATOR][GREATER] = get_token;
	// a->fta[NOT_OPERATOR][AMPER] = get_token;
	// a->fta[SPACES_BTW][PIPE] = get_token;
	// a->fta[SPACES_BTW][LESS] = get_token;
	// a->fta[SPACES_BTW][GREATER] = get_token;
	// a->fta[SPACES_BTW][AMPER] = get_token;
	// a->fta[PIPE][SPACES_NW] = get_token;
	// a->fta[OR][SPACES_NW] = get_token;
	// a->fta[AND][SPACES_NW] = get_token;
	// a->fta[LESS][SPACES_NW] = get_token;
	// a->fta[HEREDOC][SPACES_NW] = get_token;
	// a->fta[GREATER][SPACES_NW] = get_token;
	// a->fta[APPEND][SPACES_NW] = get_token;
	// a->fta[PIPE][NOT_OPERATOR] = get_token;
	// a->fta[OR][NOT_OPERATOR] = get_token;
	// a->fta[AND][NOT_OPERATOR] = get_token;
	// a->fta[LESS][NOT_OPERATOR] = get_token;
	// a->fta[HEREDOC][NOT_OPERATOR] = get_token;
	// a->fta[GREATER][NOT_OPERATOR] = get_token;
	// a->fta[APPEND][NOT_OPERATOR] = get_token;
}
