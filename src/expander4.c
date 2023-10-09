/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:40:23 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 18:37:19 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expander_helper2(t_minishell *m_s, t_tokens **a, int *i, int *size)
{
	(*i)++;
	while ((*a)->token[*i] != '"')
	{
		if ((*a)->token[*i] == '$' && (*a)->token[*i + 1] == '?')
			(*a)->token = global_replace((*a)->token, *i, size, NULL);
		else if ((*a)->token[*i] == '$')
		{
			if ((*a)->token == NULL)
				break ;
			(*a)->token = dollar_replace(m_s, (*a)->token, *i, size);
		}
		var_increase(size, i);
	}
}

void	expander_helper3(t_tokens **a, int size)
{
	if ((*a)->token != NULL)
		(*a)->token = trim_quote((*a)->token, size);
	if (!((*a)->token) || (*a)->token[0] == '\0')
	{
		free((*a)->token);
		(*a)->token = NULL;
	}
}
