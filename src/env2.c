/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:46:45 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/24 20:19:29 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envclear(t_env **lst)
{
	t_env	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free((*lst)->var_name);
			free((*lst)->var_content);
			free(*lst);
			(*lst) = tmp;
		}
	}
}

t_env	*ft_envnew(char *content)
{
	t_env	*tmp;
	char	**tab;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == NULL)
		return (NULL);
	tab = ft_mod_split(content, '=');
	tmp->var_name = ft_strdup(tab[0]);
	if (tab[1])
		tmp->var_content = ft_strdup(tab[1]);
	else
		tmp->var_content = NULL;
	tmp->next = NULL;
	free_array(tab);
	return (tmp);
}

t_env	*ft_envlast(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (tmp)
	{	
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
	if (*alst == NULL)
		*alst = new;
	else
		ft_envlast(*alst)->next = new;
}

void	yes_env(t_minishell *m_s, char **env)
{
	m_s->og_env = env;
	env_to_link(m_s);
	m_s->new_env = link_to_env(m_s);
	lvl_plus_one(m_s);
}
