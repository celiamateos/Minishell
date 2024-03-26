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
// #include "../../include/minishell.h"
// #include "../../include/minishell2.h"


// //FILE AUTOMATA.H
// typedef struct s_automata
// {
// 	void	*data;
// 	t_dlist	**token_list;
// 	char	**alphabet;
// 	char	**errors;
// 	char	*str;
// 	int		state;
// 	int		ostate;
// 	int		errorlen;
// 	int		i;
// 	int		j;
// 	void	(*fsa[20])(struct s_automata *a, void *data);
// 	void	(*fta[20][20])(struct s_automata *a, void *data);
// 	int		(*get_state)(int state, int abc_idx);
// }	t_automata;

// int		evaluate(t_automata *a);
// void	evaluate_file(t_automata *a, char *dir, void (*f)(t_automata *a, int state));


// //Automata minishell

// // typedef enum e_states
// // {
// // 	S_EMPTY,
// // 	S_CMD,
// // 	S_PIPE,
// // 	OR,
// // 	LESS,
// // 	HEREDOC,
// // 	GREATER,
// // 	APPEND,
// // 	AMPER,
// // 	AND,
// // 	INVALID,
// // 	SPACES_NW,
// // 	SPACES_BTW,
// // 	NOT_OPERATOR
// // }	t_states;

// void	alphabet_init(t_automata *a);
// void	errors_init(t_automata *a);
// int		get_state(int i, int j);

// /* Single Actions */
// void	sactions_init(t_automata *a);
// void	get_token(t_automata *a, void *data);
// // void	count_player(t_automata *a, void *data);

// /* Transition Actions */
// void	tactions_init(t_automata *a);
