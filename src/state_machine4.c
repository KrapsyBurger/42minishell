/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:34:08 by nfascia           #+#    #+#             */
/*   Updated: 2022/06/27 20:36:53 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	state_in_echo_double_quote_close(int category, char c, char **token,
t_tokens **list)
{
	if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_GENERAL)
		return (strcharjoin(token, c, STATE_IN_ECHO));
	else if (category == CHAR_WHITESPACE)
		return (strcharjoin(token, c, STATE_IN_ECHO_WHITESPACE));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_DOUBLE_QUOTE_OPEN));
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

int	state_in_echo_simple_quote_open(int category, char c, char **token,
t_tokens **list)
{	
	if (category != CHAR_SIMPLE_QUOTE && category != CHAR_EOF)
		return (strcharjoin(token, c, STATE_IN_ECHO_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_SIMPLE_QUOTE_CLOSE));
	else if (category == CHAR_EOF)
		return (501);
	(void)list;
	return (printf("bug at the echo simple quote open state"));
}

int	state_in_echo_simple_quote_close(int category, char c, char **token,
t_tokens **list)
{
	if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_ECHO_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_GENERAL)
		return (strcharjoin(token, c, STATE_IN_ECHO));
	else if (category == CHAR_WHITESPACE)
		return (strcharjoin(token, c, STATE_IN_ECHO_WHITESPACE));
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
	return (token_in_list(list, token, "echo filename", STATE_GENERAL));
}
