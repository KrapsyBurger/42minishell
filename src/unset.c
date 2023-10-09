/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:26:00 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 16:35:28 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_blender(t_minishell *m_s, char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		unset(m_s, str[i]);
		i++;
	}
}

int	unset(t_minishell *m_s, char *str)
{
	t_env	*tmp;
	t_env	*previous;
	int		bfr_size;

	tmp = m_s->lst_env;
	bfr_size = ft_envsize(tmp);
	while (tmp && ft_strcmp(str, "_") != 0)
	{
		if (bfr_size == ft_envsize(tmp) && ft_strcmp(str, tmp->var_name) == 0)
			return (free(m_s->lst_env->var_content),
				free(m_s->lst_env->var_name),
				m_s->lst_env = m_s->lst_env->next, 1);
		else if (ft_envsize(tmp) == 1 && ft_strcmp(str, tmp->var_name) == 0)
			return (previous->next = NULL, free(tmp->var_name),
				free(tmp->var_content), free(tmp), 1);
		else if (ft_strcmp(str, tmp->var_name) == 0)
			return (previous->next = tmp->next, free(tmp->var_content),
				free(tmp->var_name), free(tmp), 1);
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}
