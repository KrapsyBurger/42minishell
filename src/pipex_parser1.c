/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:39:17 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/09 19:54:26 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	new_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
	{
		return (1);
	}
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	infile_nbr(t_tokens *temp)
{
	int	nb;

	nb = 0;
	while (temp && temp->next && new_strcmp(temp->token_type, "pipe") != 0)
	{
		if (new_strcmp(temp->token_type, "stdin_redirect") == 0)
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

int	infile_fill(t_exec **ex, t_tokens **temp)
{
	t_tokens	*t;
	int			i;

	i = 0;
	t = (*temp);
	if (infile_nbr((*temp)) == 0)
		return ((*ex)->infile = NULL, 0);
	if (infile_nbr((*temp)) == 8000)
		return (1);
	(*ex)->infile = malloc(sizeof(char *) * infile_nbr((*temp)) + 8);
	while (t && t->next && new_strcmp(t->token_type, "pipe") != 0)
	{
		if (t && t->next && new_strcmp(t->token_type, "stdin_redirect") == 0)
		{
			t = t->next;
			if (new_strcmp(t->token_type, "filename") == 0)
			{
				(*ex)->infile[i] = ft_strdup(t->token);
				i++;
			}
		}
		t = t->next;
	}
	return ((*ex)->infile[i] = NULL, 0);
}

int	outfile_nbr(t_tokens *temp)
{
	int	nb;

	nb = 0;
	while (temp && temp->next && new_strcmp(temp->token_type, "pipe") != 0)
	{
		if (new_strcmp(temp->token_type, "stdout_redirect") == 0
			|| new_strcmp(temp->token_type, "append") == 0)
		{
			temp = temp->next;
			if (temp && temp->next
				&& new_strcmp(temp->token_type, "filename") == 0)
				nb++;
			else
				return (8000);
		}
		temp = temp->next;
	}
	return (nb);
}

int	tab_end(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i - 1);
}
