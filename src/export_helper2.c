/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:05:31 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 19:54:27 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_blender(t_minishell *m_s, char **cmd)
{
	int	i;
	int	tmp;
	int	global;

	i = 1;
	tmp = 0;
	global = 0;
	if (cmd[i] == NULL)
		only_export(m_s);
	else
	{
		while (cmd[i])
		{
			tmp = export(m_s, cmd[i]);
			if (tmp != 0)
				global = tmp;
			i++;
		}
	}
	g_global = global;
}
