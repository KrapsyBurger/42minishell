/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:08:58 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/24 19:26:33 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_check(t_minishell *m_s, char *verif)
{
	t_env	*tmp;

	tmp = m_s->lst_env;
	while (tmp)
	{
		if (ft_strcmp(verif, tmp->var_name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	replace_value(t_minishell *m_s, char *str)
{
	t_env	*tmp;
	char	**recup;

	recup = ft_mod_split(str, '=');
	tmp = m_s->lst_env;
	while (tmp)
	{
		if (ft_strcmp(recup[0], tmp->var_name) == 0)
		{
			free(tmp->var_content);
			if (recup[1])
				tmp->var_content = ft_strdup(recup[1]);
			else
				tmp->var_content = NULL;
		}
		tmp = tmp->next;
	}
	free_array(recup);
}

int	plus_equal(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equal = 1;
		if (str[i] == '+' && str[i + 1] == '=' && equal == 0)
			return (0);
		i++;
	}
	return (1);
}
//permet de trier des chainnes de caractere dans l'ordre croissant

void	tri_char(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i + 1] != NULL)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = ft_strdup(tab[i]);
			free(tab[i]);
			tab[i] = ft_strdup(tab[i + 1]);
			free(tab[i + 1]);
			tab[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

//permet d'afficher le cas particulier ou export serait appele seul dans le bash
//--posix

void	only_export(t_minishell *m_s)
{
	char	**export;
	int		i;

	i = -1;
	export = link_to_only_export(m_s);
	tri_char(export);
	while (export[++i])
		printf("export %s\n", export[i]);
	free_array(export);
}
