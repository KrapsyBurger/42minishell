/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:13:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/24 19:26:15 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_and_replace(t_minishell *m_s, char *name, char *new_string)
{
	t_env	*tmp;
	char	*replace;

	tmp = m_s->lst_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, name) == 0)
		{
			replace = ft_strjoin(tmp->var_content, new_string);
			free(tmp->var_content);
			tmp->var_content = ft_strdup(replace);
			free(replace);
		}
		tmp = tmp->next;
	}
}

void	export_helper(t_minishell *m_s, char **recup)
{
	char	*str_tmp;

	str_tmp = ft_strtrim(recup[0], "+");
	search_and_replace(m_s, str_tmp, recup[1]);
	free(str_tmp);
}

void	export_if_equal(t_minishell *m_s, char *str, char **recup)
{
	t_env	*tmp;

	if (export_check(m_s, recup[0]) == 0)
	{
		tmp = m_s->lst_env;
		if (tmp)
			ft_envadd_back(&tmp, ft_envnew(str));
	}
	else
		replace_value(m_s, str);
}

void	export_if_str(t_minishell *m_s, char *str, char **recup)
{
	t_env	*tmp;

	if (export_check(m_s, recup[0]) == 0)
	{
		tmp = m_s->lst_env;
		if (tmp)
			ft_envadd_back(&tmp, ft_envnew(str));
	}
	else
		replace_value(m_s, str);
}

int	export(t_minishell *m_s, char *str)
{
	char	**recup;
	char	*verif;

	verif = NULL;
	recup = ft_mod_split(str, '=');
	if (recup[0][0] >= '0' && recup[0][0] <= '9')
		return (free_array(recup), free(verif),
			ft_puterror("export: not an indentifier: ", str, " \n"),
			g_global = 1, 1);
	if (plus_equal(str) == 0)
		export_helper(m_s, recup);
	else if (ft_strchr(str, '=') != NULL)
		export_if_equal(m_s, str, recup);
	else
		export_if_str(m_s, str, recup);
	if (m_s->new_env != NULL)
		free_array(m_s->new_env);
	m_s->new_env = link_to_env(m_s);
	free_array(recup);
	free(verif);
	return (0);
}
