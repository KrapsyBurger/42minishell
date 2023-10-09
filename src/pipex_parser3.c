/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:10:07 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 20:50:30 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_helper(t_tokens **temp)
{
	(*temp) = (*temp)->next;
	if (new_strcmp((*temp)->token_type, "filename") == 0)
		(*temp) = (*temp)->next;
	if (!(*temp) || !(*temp)->next
		|| new_strcmp((*temp)->token_type, "pipe") == 0)
		return (1);
	return (0);
}

int	heredoc_nbr(t_tokens *temp)
{
	int	nb;

	nb = 0;
	while (temp && temp->next && new_strcmp(temp->token_type, "pipe") != 0)
	{
		if (new_strcmp(temp->token_type, "heredoc") == 0)
		{
			temp = temp->next;
			if (new_strcmp(temp->token_type, "filename") == 0)
				nb++;
			else
				return (8000);
		}
		temp = temp->next;
	}
	return (nb);
}

int	heredoc_fill(t_exec **ex, t_tokens **temp, t_minishell *ms)
{
	t_tokens	*t;

	t = (*temp);
	if (heredoc_nbr((*temp)) == 0)
		return ((*ex)->heredoc_string = NULL, 0);
	if (heredoc_nbr ((*temp)) == 8000)
		return ((*ex)->heredoc_string = NULL, 1);
	to_heredoc(ex, (*temp));
	while (t && t->next && new_strcmp(t->token_type, "pipe") != 0)
	{
		if (t && t->next && new_strcmp(t->token_type, "heredoc") == 0)
		{
			t = t->next;
			if (new_strcmp(t->token_type, "filename") == 0)
			{
				if ((*ex)->heredoc_filename != NULL)
					free((*ex)->heredoc_filename);
				(*ex)->heredoc_filename = ft_strdup(t->token);
				if (ms->heredoc_bool == 0)
					heredoc(ex, ms);
			}
		}
		t = t->next;
	}
	return (0);
}

int	cmp_helper(char *s)
{
	if (new_strcmp(s, "stdout_redirect") == 0
		|| new_strcmp(s, "stdin_redirect") == 0
		|| new_strcmp(s, "append") == 0
		|| new_strcmp(s, "heredoc") == 0)
	{
		return (0);
	}
	return (1);
}
