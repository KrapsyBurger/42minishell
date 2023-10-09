/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:39:49 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/17 17:21:47 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_append(t_exec **ex, t_tokens *temp)
{
	while (temp && temp->next)
	{
		if (new_strcmp(temp->token_type, "stdout_redirect") == 0)
			(*ex)->to_append = 0;
		else if (new_strcmp(temp->token_type, "append") == 0)
			(*ex)->to_append = 1;
		temp = temp->next;
	}
	return (0);
}

int	outfile_fill(t_exec **ex, t_tokens **temp)
{
	t_tokens	*temp1;
	int			i;

	i = 0;
	temp1 = (*temp);
	if (outfile_nbr((*temp)) == 0)
		return ((*ex)->outfile = NULL, 0);
	else if (outfile_nbr((*temp)) == 8000)
		return (1);
	(*ex)->outfile = malloc(sizeof(char *) * outfile_nbr((*temp)) + 8);
	while (temp1 && temp1->next && new_strcmp(temp1->token_type, "pipe") != 0)
	{
		if (new_strcmp(temp1->token_type, "stdout_redirect") == 0
			|| new_strcmp(temp1->token_type, "append") == 0)
		{
			temp1 = temp1->next;
			if (new_strcmp(temp1->token_type, "filename") == 0)
			{
				(*ex)->outfile[i] = ft_strdup(temp1->token);
				i++;
			}
		}
		temp1 = temp1->next;
	}
	return ((*ex)->outfile[i] = NULL, is_append(ex, (*temp)));
}

int	cmd_nbr(t_tokens *temp)
{
	int	nb;

	nb = 0;
	while (temp && temp->next && new_strcmp(temp->token_type, "pipe") != 0)
	{
		if (new_strcmp(temp->token_type, "stdout_redirect") == 0
			|| new_strcmp(temp->token_type, "stdin_redirect") == 0
			|| new_strcmp(temp->token_type, "append") == 0)
		{
			temp = temp->next;
			if (new_strcmp(temp->token_type, "filename") == 0)
				temp = temp->next;
		}
		else if (temp && temp->next
			&& (new_strcmp(temp->token_type, "filename") == 0))
		{
			nb++;
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	return (nb);
}

int	cmd_fill(t_exec **ex, t_tokens **temp, int i)
{
	t_tokens	*t;

	t = (*temp);
	if (cmd_nbr((*temp)) == 0)
		return (0);
	(*ex)->cmd = malloc(sizeof(char *) * cmd_nbr((*temp)) + 8);
	while (t && t->next && new_strcmp(t->token_type, "pipe") != 0)
	{
		if (cmp_helper(t->token_type) == 0)
		{
			if (cmd_helper(&t) == 1)
				break ;
		}
		else if (new_strcmp(t->token_type, "filename") == 0 && t->token != NULL)
		{
			(*ex)->cmd[i] = ft_strdup(t->token);
			i++;
			t = t->next;
		}
		else
			t = t->next;
	}
	return ((*ex)->cmd[i] = NULL, 0);
}

int	list_fill(t_exec **ex, t_tokens **temp, t_minishell *ms)
{
	while ((*temp))
	{
		if (list_fill_helper(ex, temp, ms) == 1)
			return (1);
		while ((*temp) && new_strcmp((*temp)->token_type, "pipe") != 0)
			(*temp) = (*temp)->next;
		if ((*temp) == NULL)
			break ;
		if (new_strcmp((*temp)->token_type, "pipe") == 0
			&& (*temp)->next->token == NULL)
			return (1);
		else if (new_strcmp((*temp)->token_type, "pipe") == 0)
		{
			(*temp) = (*temp)->next;
			(*ex)->next = malloc(sizeof(t_exec));
			init_ex(ex);
		}
	}
	return (0);
}
