/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:20:10 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 20:20:42 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_env(t_minishell *m_s)
{
	char	buff[4096];
	char	*tmp;
	char	*join;

	tmp = getcwd(buff, 4096);
	join = ft_strjoin("PWD=", tmp);
	ft_envadd_back(&m_s->lst_env, ft_envnew(join));
	ft_envadd_back(&m_s->lst_env, ft_envnew(ft_strdup("SHLVL=1")));
	ft_envadd_back(&m_s->lst_env, ft_envnew(ft_strdup("_=/usr/bin/env")));
}

void	lvl_plus_one(t_minishell *m_s)
{
	t_env	*tmp;
	int		i;
	int		nope;

	nope = 0;
	tmp = m_s->lst_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "SHLVL") == 0)
		{
			i = ft_atoi(tmp->var_content);
			i++;
			free(tmp->var_content);
			tmp->var_content = ft_itoa(i);
			nope = 1;
		}
		tmp = tmp->next;
	}
	if (nope == 0)
		export(m_s, "SHLVL=0");
}
