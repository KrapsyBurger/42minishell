/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:30:46 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 20:15:32 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_there_pipe(t_tokens **token)
{
	t_tokens	*temp;

	temp = (*token);
	while (temp && temp->next)
	{
		if (new_strcmp(temp->token_type, "pipe") == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	is_there_exit(t_tokens **token, int *pipenb)
{
	if (new_strcmp((*token)->token, "exit") == 0)
		return (1);
	while ((*token) && (*token)->next)
	{
		if (new_strcmp((*token)->token_type, "pipe") == 0)
		{
			(*pipenb)++;
			if (new_strcmp((*token)->next->token, "exit") == 0)
			{
				(*token) = (*token)->next;
				return (1);
			}
		}
		(*token) = (*token)->next;
	}
	return (0);
}

int	exit_checker_helper(t_tokens **token, t_tokens **temp)
{
	if (is_there_pipe(token) == 0)
	{
		if ((*temp)->token != NULL)
		{
			g_global = ft_atoi((*temp)->token);
			if (g_global > 255)
			g_global = 0;
		}
		else
			g_global = 0;
		return (5);
	}
	else if ((*temp)->token != NULL)
	{
		g_global = ft_atoi((*temp)->token);
		if (g_global > 255)
			g_global = 0;
	}
	else
		g_global = 0;
	return (2);
}

int	exit_checker(t_tokens **token)
{
	t_tokens	*t;
	int			pipenb;

	t = (*token);
	pipenb = 0;
	if (is_there_exit(&t, &pipenb) == 1)
	{
		if (new_strcmp(t->token, "exit") == 0)
		{
			t = t->next;
			if (t->next != NULL && new_strcmp(t->token_type, "filename") == 0)
				if (t->next->next != NULL
					&& new_strcmp(t->next->token_type, "pipe") != 0)
					return (g_global = 1,
						ft_putstr_fd("exit\nexit: too many arguments.\n", 2), 2);
			if (is_num(t->token) == 0
				&& new_strcmp(t->token_type, "filename") == 0)
				return (g_global = 2,
					ft_putstr_fd("exit\nexit: numeric arguments required.\n", 2)
					, 5);
			else
				return (exit_checker_helper(token, &t));
		}
	}
	return (0);
}

int	exit_return(t_tokens **token, t_minishell *m_s)
{
	ft_free_token(token);
	free(m_s->input);
	free_array(m_s->new_env);
	ft_envclear(&m_s->lst_env);
	free((*token));
	free(m_s);
	return (g_global);
}
