/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:34:02 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 20:52:55 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	state_in_heredoc_token(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_GENERAL)
	{
		token_in_list(list, token, "heredoc", 0);
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	}
	else if (category == CHAR_WHITESPACE)
		return (token_in_list(list, token, "heredoc", STATE_GENERAL));
	else if (category == CHAR_DOUBLE_QUOTE)
	{
		token_in_list(list, token, "heredoc", 0);
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	}
	else if (category == CHAR_SIMPLE_QUOTE)
	{
		token_in_list(list, token, "heredoc", 0);
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	}
	else if (category == CHAR_STDIN_REDIRECT)
		return (500);
	return (500);
}

int	state_in_stdout_redirect(int category, char c, char **token,
t_tokens **list)
{
	if (category == CHAR_GENERAL)
	{
		token_in_list(list, token, "stdout_redirect", 0);
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	}
	else if (category == CHAR_WHITESPACE)
		return (token_in_list(list, token, "stdout_redirect", STATE_GENERAL));
	else if (category == CHAR_DOUBLE_QUOTE)
	{
		token_in_list(list, token, "stdout_redirect", 0);
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	}
	else if (category == CHAR_SIMPLE_QUOTE)
	{
		token_in_list(list, token, "stdout_redirect", 0);
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	}
	else if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_APPEND));
	return (500);
}

int	state_in_append(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_GENERAL)
	{
		token_in_list(list, token, "append", 0);
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	}
	else if (category == CHAR_DOUBLE_QUOTE)
	{
		token_in_list(list, token, "append", 0);
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	}
	else if (category == CHAR_SIMPLE_QUOTE)
	{
		token_in_list(list, token, "append", 0);
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	}
	else if (category == CHAR_WHITESPACE)
		return (token_in_list(list, token, "append", STATE_GENERAL));
	return (500);
}

int	state_in_double_quote_open(int category, char c, char **token,
t_tokens **list)
{	
	if (category != CHAR_DOUBLE_QUOTE && category != CHAR_EOF)
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_CLOSE));
	else if (category == CHAR_EOF)
		return (501);
	(void)list;
	return (printf("bug at the double_quote_open state"));
}

int	state_in_double_quote_close(int category, char c, char **token,
t_tokens **list)
{
	if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_GENERAL)
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_PIPE)
		token_in_list(list, token, "filename double quote", 0);
	if (category == CHAR_PIPE)
		return (strcharjoin(token, c, STATE_IN_PIPE));
	else if (category == CHAR_AMPERSAND)
		token_in_list(list, token, "filename double quote", 0);
	if (category == CHAR_AMPERSAND)
		return (strcharjoin(token, c, STATE_IN_AMPERSAND));
	else if (category == CHAR_STDIN_REDIRECT)
		token_in_list(list, token, "filename double quote", 0);
	if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		token_in_list(list, token, "filename double quote", 0);
	if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDOUT_REDIRECT));
	return (token_in_list(list, token, "filename double quote",
			STATE_GENERAL));
}
