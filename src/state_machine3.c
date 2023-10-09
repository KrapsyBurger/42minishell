/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:34:05 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/19 14:38:50 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	state_in_simple_quote_open(int category, char c, char **token,
t_tokens **list)
{	
	if (category != CHAR_SIMPLE_QUOTE && category != CHAR_EOF)
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_CLOSE));
	else if (category == CHAR_EOF)
		return (501);
	(void)list;
	return (printf("bug at the simple quote open state"));
}

int	state_in_simple_quote_close(int category, char c, char **token,
t_tokens **list)
{
	if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_GENERAL)
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	else if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_PIPE)
		token_in_list(list, token, "filename single quote", 0);
	if (category == CHAR_PIPE)
		return (strcharjoin(token, c, STATE_IN_PIPE));
	else if (category == CHAR_AMPERSAND)
		token_in_list(list, token, "filename single quote", 0);
	if (category == CHAR_AMPERSAND)
		return (strcharjoin(token, c, STATE_IN_AMPERSAND));
	else if (category == CHAR_STDIN_REDIRECT)
		token_in_list(list, token, "filename single quote", 0);
	if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		token_in_list(list, token, "filename single quote", 0);
	else if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDOUT_REDIRECT));
	return (token_in_list(list, token, "filename single quote",
			STATE_GENERAL));
}

int	state_in_echo_whitespace(int category, char c, char **token,
t_tokens **list)
{
	if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_PIPE)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_PIPE)
		return (strcharjoin(token, c, STATE_IN_PIPE));
	else if (category == CHAR_AMPERSAND)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_AMPERSAND)
		return (strcharjoin(token, c, STATE_IN_AMPERSAND));
	else if (category == CHAR_STDIN_REDIRECT)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDOUT_REDIRECT));
	else if (category == CHAR_EOF)
		return (token_in_list(list, token, "echo filename", STATE_GENERAL));
	else if (category != CHAR_WHITESPACE)
		return (strcharjoin(token, c, STATE_IN_ECHO));
	return (STATE_IN_ECHO_WHITESPACE);
}

int	state_in_echo(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_GENERAL)
		return (strcharjoin(token, c, STATE_IN_ECHO));
	else if (category == CHAR_WHITESPACE)
		return (strcharjoin(token, c, STATE_IN_ECHO_WHITESPACE));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_DOUBLE_QUOTE_CLOSE));
	if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_PIPE)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_PIPE)
		return (strcharjoin(token, c, STATE_IN_PIPE));
	else if (category == CHAR_AMPERSAND)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_AMPERSAND)
		return (strcharjoin(token, c, STATE_IN_AMPERSAND));
	else if (category == CHAR_STDIN_REDIRECT)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		token_in_list(list, token, "echo filename", 0);
	if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDOUT_REDIRECT));
	return (token_in_list(list, token, "echo filename", STATE_GENERAL));
}

int	state_in_echo_double_quote_open(int category, char c, char **token,
t_tokens **list)
{	
	if (category != CHAR_DOUBLE_QUOTE && category != CHAR_EOF)
		return (strcharjoin(token, c, STATE_IN_ECHO_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_DOUBLE_QUOTE_CLOSE));
	else if (category == CHAR_EOF)
		return (501);
	(void)list;
	return (printf("bug at the echo double quote open state"));
}
