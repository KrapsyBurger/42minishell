/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:33:59 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/18 21:29:02 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	state_general(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_GENERAL)
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	else if (category == CHAR_WHITESPACE)
		return (STATE_GENERAL);
	else if (category == CHAR_PIPE)
		return (strcharjoin(token, c, STATE_IN_PIPE));
	else if (category == CHAR_AMPERSAND)
		return (strcharjoin(token, c, STATE_IN_AMPERSAND));
	else if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_STDOUT_REDIRECT));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	else if (category == EOF)
		return (STATE_GENERAL);
	(void)list;
	return (printf("bug at the general state"));
}

int	state_in_filename(int category, char c, char **t, t_tokens **list)
{
	if (category == CHAR_GENERAL)
		return (strcharjoin(t, c, STATE_IN_FILENAME));
	else if (category == CHAR_DOUBLE_QUOTE)
		return (strcharjoin(t, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	else if (category == CHAR_SIMPLE_QUOTE)
		return (strcharjoin(t, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	else if (category == CHAR_PIPE)
		token_in_list(list, t, "filename", 0);
	if (category == CHAR_PIPE)
		return (strcharjoin(t, c, STATE_IN_PIPE));
	else if (category == CHAR_AMPERSAND)
		token_in_list(list, t, "filename", 0);
	if (category == CHAR_AMPERSAND)
		return (strcharjoin(t, c, STATE_IN_AMPERSAND));
	else if (category == CHAR_STDIN_REDIRECT)
		token_in_list(list, t, "filename", 0);
	if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(t, c, STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		token_in_list(list, t, "filename", 0);
	if (category == CHAR_STDOUT_REDIRECT)
		return (strcharjoin(t, c, STATE_IN_STDOUT_REDIRECT));
	if (ft_strcmp((*t), "echo") == 0)
		return (token_in_list(list, t, "echo cmd", STATE_IN_ECHO_WHITESPACE));
	return (token_in_list(list, t, "filename", STATE_GENERAL));
}

int	state_in_pipe(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_PIPE)
		return (500);
	else if (category == CHAR_GENERAL)
	{
		token_in_list(list, token, "pipe", 0);
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	}
	else if (category == CHAR_DOUBLE_QUOTE)
	{
		token_in_list(list, token, "pipe", 0);
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	}
	else if (category == CHAR_SIMPLE_QUOTE)
	{
		token_in_list(list, token, "pipe", 0);
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	}
	else if (category == CHAR_WHITESPACE)
		return (token_in_list(list, token, "pipe", STATE_GENERAL));
	else if (category == CHAR_STDIN_REDIRECT)
		return (token_in_list(list, token, "pipe", STATE_IN_STDIN_REDIRECT));
	else if (category == CHAR_STDOUT_REDIRECT)
		return (token_in_list(list, token, "pipe", STATE_IN_STDOUT_REDIRECT));
	return (500);
}

int	state_in_ampersand(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_GENERAL)
	{
		token_in_list(list, token, "ampersand", 0);
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	}
	else if (category == CHAR_WHITESPACE)
		return (token_in_list(list, token, "ampersand", STATE_GENERAL));
	else if (category == CHAR_DOUBLE_QUOTE)
	{
		token_in_list(list, token, "ampersand", 0);
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	}
	else if (category == CHAR_SIMPLE_QUOTE)
	{
		token_in_list(list, token, "ampersand", 0);
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	}
	else if (category == CHAR_AMPERSAND)
		return (500);
	return (printf("bug at the ampersand state"));
}

int	state_in_stdin_redirect(int category, char c, char **token, t_tokens **list)
{
	if (category == CHAR_GENERAL)
	{
		token_in_list(list, token, "stdin_redirect", 0);
		return (strcharjoin(token, c, STATE_IN_FILENAME));
	}
	else if (category == CHAR_WHITESPACE)
		return (token_in_list(list, token, "stdin_redirect", STATE_GENERAL));
	else if (category == CHAR_DOUBLE_QUOTE)
	{
		token_in_list(list, token, "stdin_redirect", 0);
		return (strcharjoin(token, c, STATE_IN_DOUBLE_QUOTE_OPEN));
	}
	else if (category == CHAR_SIMPLE_QUOTE)
	{
		token_in_list(list, token, "stdin_redirect", 0);
		return (strcharjoin(token, c, STATE_IN_SIMPLE_QUOTE_OPEN));
	}
	else if (category == CHAR_STDIN_REDIRECT)
		return (strcharjoin(token, c, STATE_IN_HEREDOC_TOKEN));
	return (500);
}
