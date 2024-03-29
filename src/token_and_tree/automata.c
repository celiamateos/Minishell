/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// @brief Check type and return char position in states[]
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

// @brief Main function of validation with automata
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
	return (a->state);
}

// @brief Alphabet definitions
void	alphabet_init(t_automata *a)
{
	a->alphabet = ft_clear_sarradd(a->alphabet, "0");
	a->alphabet = ft_clear_sarradd(a->alphabet, "1");
	a->alphabet = ft_clear_sarradd(a->alphabet, "2");
	a->alphabet = ft_clear_sarradd(a->alphabet, "3");
	a->alphabet = ft_clear_sarradd(a->alphabet, "4");
	a->alphabet = ft_clear_sarradd(a->alphabet, "5");
	a->alphabet = ft_clear_sarradd(a->alphabet, "6");
	a->alphabet = ft_clear_sarradd(a->alphabet, "7");
	a->alphabet = ft_clear_sarradd(a->alphabet, "8");
}

int	get_state(int i, int j)
{
	const int	states[][6] = {{9, 2, 2, 5, 1, 7},
	{9, 2, 2, 1, 2, 1},
	{2, 2, 2, 2, 2, 2},
	{9, 2, 2, 5, 1, 2},
	{9, 2, 2, 5, 1, 2},
	{9, 2, 2, 2, 1, 10},
	{6, 6, 6, 6, 6, 6},
	{7, 7, 7, 7, 7, 7},
	{6, 3, 4, 8, 8, 10},
	{6, 3, 4, 9, 8, 10},
	{10, 10, 10, 10, 10, 10},
	};

	return (states[i][j]);
}

// @brief Error strings to print when automata finish on a non ending state.
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
