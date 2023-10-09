/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exec_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:00:52 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/18 20:34:06 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_env(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
}

void	bltn_select(char **cmd, t_minishell *m_s)
{
	if (new_strcmp(cmd[0], "export") == 0)
		export_blender(m_s, cmd);
	if (new_strcmp(cmd[0], "cd") == 0)
		cd(m_s, cmd);
	if (new_strcmp(cmd[0], "pwd") == 0)
		pwd();
	if (new_strcmp(cmd[0], "unset") == 0)
		unset_blender(m_s, cmd);
	if (new_strcmp(cmd[0], "env") == 0)
	{
		if (m_s->new_env != NULL)
			free_array(m_s->new_env);
		m_s->new_env = link_to_env(m_s);
		ft_print_env(m_s->new_env);
	}
	if (new_strcmp(cmd[0], "echo") == 0)
		echo(cmd[1]);
}

int	is_bltn(char *str)
{
	if (new_strcmp(str, "echo") == 0)
		return (0);
	if (new_strcmp(str, "cd") == 0)
		return (0);
	if (new_strcmp(str, "pwd") == 0)
		return (0);
	if (new_strcmp(str, "export") == 0)
		return (0);
	if (new_strcmp(str, "unset") == 0)
		return (0);
	if (new_strcmp(str, "env") == 0)
		return (0);
	return (1);
}
