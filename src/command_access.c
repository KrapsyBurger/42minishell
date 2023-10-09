/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:43:14 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/22 12:52:59 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**path_splitter(t_env *lst_env)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	paths = ft_mod_split(lst_env->var_content, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return (paths);
}

void	minisplit(t_exec *ex)
{
	t_exec	*tmp;

	tmp = ex;
	while (tmp)
	{
		tmp->first = ft_strdup(tmp->cmd[0]);
		tmp->fd_rd = -2;
		tmp->fd_wr = -2;
		tmp = tmp->next;
	}
}

int	verif_access(char **paths, t_exec *tmp)
{
	int		i;
	char	*stmp;
	char	*correct_path;

	i = -1;
	while (paths[++i] != NULL)
	{
		stmp = ft_strjoin(paths[i], tmp->first);
		if (access(stmp, F_OK) == 0)
		{
			correct_path = ft_strdup(stmp);
			free(tmp->first);
			tmp->first = ft_strdup(correct_path);
			free(correct_path);
			return (free(stmp), 1);
		}
		free(stmp);
	}
	return (0);
}

int	verif_command(t_exec *ex, char **paths)
{
	t_exec	*tmp;
	int		i;

	i = 0;
	tmp = ex;
	minisplit(ex);
	while (tmp)
	{
		i = verif_access(paths, tmp);
		if (i == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	command_checker(t_minishell *m_s, t_exec *ex, char *str)
{
	char	**paths;
	t_env	*tmp;

	tmp = m_s->lst_env;
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
	{
		if (access(str, F_OK) == 0)
		{
			if (access(str, X_OK) == 0)
				return (ex->first = ft_strdup(str), 1);
			else
				return (ex->first = ft_strdup(str), 2);
		}
		return (ex->first = ft_strdup(str), 0);
	}
	while (tmp)
	{
		if (ft_strnstr(tmp->var_name, "PATH", 4) != NULL)
			paths = path_splitter(tmp);
		tmp = tmp->next;
	}
	if (verif_command(ex, paths) == 1)
		return (free_array(paths), 1);
	free_array(paths);
	return (0);
}
