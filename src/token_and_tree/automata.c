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
int	idx(int alphabet[], int c)
{
	int	i;

	// i = -1;
	// 	while (++i < 9)
	// {
	// 	printf("Alfabet %d\n", alphabet[i]);
	// }
// printf("TYPE %d\n", c);
	i = -1;
	while (++i < 9)
	{
	// printf("I  %d\n", i);
		if (alphabet[i] == c)
			break ;
	}	
	// printf("I  %d\n", i);
	if (i == 4)
		i = 3;
	else if (i >= 5)
		i = 4;
	printf("I  %d\n", i);
	return (i);
}

int	evaluate(t_automata *a)
{
	t_token	*token;
	t_dlist	**token_list;

	a->ostate = 0;
	a->i = -1;
	token_list = a->token_list;

int alpha[9];

	alpha[0] = 0; //CMD
	alpha[1] = 1; //PIPE
	alpha[2] = 2; //OPER
	alpha[3] = 3; //PARENT_OP
	alpha[4] = 4; //PARENT_CL
	alpha[5] = 5; //HEREDOC
	alpha[6] = 6; //REDIR_IN
	alpha[7] = 7; //REDIR_OUT
	alpha[8] = 8; //APPEND_OUT

	while (*token_list)
	{
		token = (*token_list)->content;
		a->state = a->get_state(a->state, idx((alpha), token->type));
		printf("a->state %d\n", a->state);
		printf("a->ostate %d\n", a->ostate);
		if (a->ostate == -1)
		{
			printf("CHECK First time conditions");
			a->ostate = 0;
		}
		// if (a->fsa[a->state])
		// 	a->fsa[a->state](a, a->data);
		// if (a->fta[a->ostate][a->state])
		// 	a->fta[a->ostate][a->state](a, a->data);
		a->ostate = a->state;
		(*token_list) = (*token_list)->next;

	}
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
void	alphabet_init(t_automata **a)
{
	int alpha[9];

	alpha[0] = 0; //CMD
	alpha[1] = 1; //PIPE
	alpha[2] = 2; //OPER
	alpha[3] = 3; //PARENT_OP
	alpha[4] = 4; //PARENT_CL
	alpha[5] = 5; //HEREDOC
	alpha[6] = 6; //REDIR_IN
	alpha[7] = 7; //REDIR_OUT
	alpha[8] = 8; //APPEND_OUT
	*(*a)->alphabet = alpha;
}

int	get_state(int i, int j)
{
	const int states[][6] = {
//  CMD,|, &,(),<>,
	{9, 2, 2, 6, 1, 8},   // 0  Empty input (First input)
	{9, 2, 2, 1, 2, 1},   // 1  Redirs with no cmd
	{2, 2, 2, 2, 2, 2},   // 2  Oper syntax error
	{9, 2, 2, 6, 1, 2},   // 3  Pipe open
	{9, 2, 2, 6, 1, 2},   // 4  Oper (&& ||) open
	{7, 3, 4, 5, 5, 10},   // 5  REDIRS open
	{9, 2, 2, 2, 1, 10},   // 6  Parentheses open
	{7, 7, 7, 7, 7, 7},   // 7 CMD syntax error
	{8, 8, 8, 8, 8, 8},   // 8 Invalid input
	{7, 3, 4, 9, 5, 10},   // 9 CMD
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
	a->errors = ft_sarradd(a->errors, "Open double quotes");
	a->errors = ft_sarradd(a->errors, "Open single quotes");
	a->errors = ft_sarradd(a->errors, "Pipe open");
	a->errors = ft_sarradd(a->errors, "Or open");
	a->errors = ft_sarradd(a->errors, "Less open");
	a->errors = ft_sarradd(a->errors, "Heredoc open");
	a->errors = ft_sarradd(a->errors, "Greater open");
	a->errors = ft_sarradd(a->errors, "Append open");
	a->errors = ft_sarradd(a->errors, "& Found");
	a->errors = ft_sarradd(a->errors, "And open");
	a->errors = ft_sarradd(a->errors, "Invalid input");
	// a->errorlen = ft_sarrsize(a->errors);
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
