/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demallocage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:11:09 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:54:19 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_last_node(t_tokens **tk)
{
	t_tokens	*temp;

	temp = (*tk);
	while (temp && temp->next)
		temp = temp->next;
	temp->token = NULL;
	temp->token_type = NULL;
	temp = NULL;
	return (0);
}

int	ft_free_token(t_tokens **list)
{
	t_tokens	*temp;

	temp = (*list)->next;
	while (temp && temp->next)
	{
		free((*list)->token);
		free((*list)->token_type);
		free((*list));
		(*list) = temp;
		temp = temp->next;
	}
	free((*list)->token);
	free((*list)->token_type);
	free(temp);
	free((*list));
	(*list) = malloc(sizeof(t_tokens));
	(*list)->next = NULL;
	return (0);
}

int	exit_free_token(t_tokens **list)
{
	t_tokens	*temp;

	temp = (*list)->next;
	while (temp && temp->next)
	{
		free((*list)->token);
		free((*list)->token_type);
		free((*list));
		(*list) = temp;
		temp = temp->next;
	}
	free(temp);
	if ((*list)->token != NULL)
		free((*list)->token);
	if ((*list)->token_type != NULL)
		free((*list)->token_type);
	free((*list));
	return (0);
}

void	free_array(char **twoD)
{
	int	i;

	i = 0;
	while (twoD[i] != NULL)
		free(twoD[i++]);
	free(twoD);
}

void	demallocage(t_minishell *m_s)
{
	clear_history();
	if (m_s->new_env != NULL)
		free_array(m_s->new_env);
	ft_envclear(&m_s->lst_env);
	free(m_s->lst_env);
	free(m_s);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
