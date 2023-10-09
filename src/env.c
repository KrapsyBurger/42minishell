/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:22:59 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/17 20:16:49 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//permet de pouvoir passer d'un environnement en tableau de char, vers un 
//environnement en liste chainee 

void	env_to_link(t_minishell *m_s)
{
	int	i;

	i = 0;
	while (m_s->og_env[i])
		ft_envadd_back(&m_s->lst_env, ft_envnew(m_s->og_env[i++]));
}

//permet d'obtenir la taille de la liste chainnee contenant l'environnement

//renvoie un int

int	ft_envsize(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{	
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	ft_custom_envsize(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{	
		if (tmp->var_content != NULL)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

//permet de pouvoir passer d'un environnement en liste chainee, vers un
//environnement en tableau char. 

//renvoie un tableau de char **

char	**link_to_env(t_minishell *m_s)
{
	int		i;
	int		lst_size;
	t_env	*tmp;
	char	*tmp2;
	char	**env;

	i = 0;
	tmp = m_s->lst_env;
	lst_size = ft_custom_envsize(tmp);
	env = malloc(sizeof(char *) * lst_size + 8);
	while (lst_size != 0)
	{
		if (tmp->var_content != NULL)
		{
			tmp2 = ft_strjoin(tmp->var_name, "=");
			env[i] = ft_strjoin(tmp2, tmp->var_content);
			free(tmp2);
			i++;
			lst_size--;
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

//permet de pouvoir passer d'un environnement en liste chainee, vers un
//environnement en tableau char, pour gerer le cas de export seul dans
//bash --posix. 

//renvoie un tableau de char **

char	**link_to_only_export(t_minishell *m_s)
{
	int		i;
	t_env	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	**env;

	i = 0;
	tmp = m_s->lst_env;
	env = malloc(sizeof(char *) * (ft_envsize(tmp) + 1));
	while (ft_envsize(tmp))
	{
		if (tmp->var_content)
		{
			tmp2 = ft_strjoin(tmp->var_name, "=\"");
			tmp3 = ft_strjoin(tmp2, tmp->var_content);
			env[i++] = ft_strjoin(tmp3, "\"");
			free(tmp2);
			free(tmp3);
		}
		else
			env[i++] = ft_strdup(tmp->var_name);
		tmp = tmp->next;
	}
	return (env[i] = NULL, env);
}
