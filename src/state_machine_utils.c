/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:33:55 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/08 20:11:21 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	translate(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (CHAR_WHITESPACE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '\0')
		return (CHAR_EOF);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == '<')
		return (CHAR_STDIN_REDIRECT);
	else if (c == '>')
		return (CHAR_STDOUT_REDIRECT);
	else if (c == '"')
		return (CHAR_DOUBLE_QUOTE);
	else if (c == '\'')
		return (CHAR_SIMPLE_QUOTE);
	else
		return (CHAR_GENERAL);
}

int	token_in_list(t_tokens **list, char **token, char *token_type, int ret)
{
	t_tokens	*temp;

	temp = (*list);
	while (temp && temp->next)
	{
		temp = temp->next;
	}
	temp->token = ft_strdup((*token));
	temp->token_type = ft_strdup(token_type);
	temp->next = malloc(sizeof(t_tokens));
	temp = temp->next;
	temp->next = NULL;
	free((*token));
	(*token) = malloc(sizeof(char) * 1);
	(*token)[0] = '\0';
	return (ret);
}

int	strcharjoin(char **token, char c, int state)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen((*token)) + 2);
	while ((*token)[i])
	{
		ret[i] = (*token)[i];
		i++;
	}
	ret[i] = c;
	i++;
	ret[i] = '\0';
	free((*token));
	(*token) = ft_strdup(ret);
	free(ret);
	return (state);
}
