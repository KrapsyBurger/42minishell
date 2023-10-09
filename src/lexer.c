/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:11:47 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 15:43:59 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	tokeniser(char *s,
int (**state_func)(int, char c, char **, t_tokens **list), t_tokens **list)
{
	int		category;
	int		current_state;
	char	*token;
	int		index;

	token = malloc(sizeof(char) * 1);
	token[0] = '\0';
	index = 0;
	category = 0;
	current_state = STATE_GENERAL;
	while (category != CHAR_EOF)
	{
		category = translate(s[index]);
		current_state = state_func[current_state](category,
				s[index], &token, list);
		if (current_state == 500)
			return (free(token), ft_putstr_fd("Syntax error.\n", 2),
				g_global = 2, 42);
		else if (current_state == 501)
			return (free(token), ft_putstr_fd("Quote unclosed.\n", 2), 42);
		index++;
	}
	return (free(token), free_last_node(list), 0);
}

int	print_list(t_tokens **tokens)
{
	t_tokens	*temp;

	temp = (*tokens);
	while (temp && temp->next)
	{
		printf("Token : %s\n", temp->token);
		printf("Type du token : %s\n\n", temp->token_type);
		temp = temp->next;
	}
	return (0);
}

int	lexer(char *input, t_tokens **list)
{
	int			(**state_func)(int, char, char **, t_tokens **list);

	state_func = malloc(sizeof(state_func) * 18);
	state_func[0] = &state_general;
	state_func[1] = &state_in_filename;
	state_func[2] = &state_in_pipe;
	state_func[3] = &state_in_ampersand;
	state_func[4] = &state_in_stdin_redirect;
	state_func[5] = &state_in_heredoc_token;
	state_func[6] = &state_in_stdout_redirect;
	state_func[7] = &state_in_append;
	state_func[8] = &state_in_double_quote_open;
	state_func[9] = &state_in_double_quote_close;
	state_func[10] = &state_in_simple_quote_open;
	state_func[11] = &state_in_simple_quote_close;
	state_func[12] = &state_in_echo;
	state_func[13] = &state_in_echo_whitespace;
	state_func[14] = &state_in_echo_double_quote_open;
	state_func[15] = &state_in_echo_double_quote_close;
	state_func[16] = &state_in_echo_simple_quote_open;
	state_func[17] = &state_in_echo_simple_quote_close;
	if (tokeniser(input, state_func, list) == 42)
		return (free(state_func), 42);
	free(state_func);
	return (0);
}
