/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:59:52 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:26:40 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//permet d'aller dans la structure d'environnement et de modifier PATH 
//et OLDPATH en fonction de que cette fonction recoie

void	pwd_replace(t_minishell *m_s, char *path, char *old_path)
{
	t_env	*tmp;

	tmp = m_s->lst_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "PWD") == 0)
		{
			free(tmp->var_content);
			tmp->var_content = ft_strdup(path);
		}
		if (ft_strcmp(tmp->var_name, "OLDPWD") == 0)
		{
			free(tmp->var_content);
			tmp->var_content = ft_strdup(old_path);
		}
		tmp = tmp->next;
	}
	free(old_path);
}

int	d_array_size(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void	cd_helper(char **cmd)
{
	struct stat	st;

	if (stat(cmd[1], &st))
		ft_puterror("Minishell: cd: No such file or directory: ", cmd[1], "\n");
	else
		ft_puterror("Minishell: cd: Permission denied: ", cmd[1], "\n");
}

//permet de modifier le path et le oldpath en fonction de ce qui est envoye dans
//cd, retourne au home si on lui envoie un str NULL, et va a str si et seulement
//si str contient un path correct. Ecris une erreur si chdir renvoie 1

void	cd(t_minishell *m_s, char **cmd)
{
	char			*old_path;
	char			*tmp;
	char			buff[4096];

	if (d_array_size(cmd) > 2)
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
	else
	{
		tmp = getcwd(buff, 4096);
		if (tmp)
			old_path = ft_strdup(tmp);
		else
			old_path = search_env(m_s, "HOME");
		if (cmd[1] == NULL)
		{
			if (chdir(getenv("HOME")) == -1)
				ft_putstr_fd("Minishell: Error: can't find $HOME\n", 2);
			else
				pwd_replace(m_s, getcwd(buff, 4096), old_path);
		}
		else if (chdir(cmd[1]) == -1)
			cd_helper(cmd);
		else
			pwd_replace(m_s, getcwd(buff, 4096), old_path);
	}
}
