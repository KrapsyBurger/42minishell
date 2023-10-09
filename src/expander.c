/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:00:49 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 18:36:41 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_env(t_minishell *m_s, char *analyse)
{
	t_env	*tmp;

	tmp = m_s->lst_env;
	while (tmp)
	{
		if (ft_strcmp(analyse, tmp->var_name) == 0)
			return (ft_strdup(tmp->var_content));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*replacer(char *str, char *analyse, char *copy, int indice)
{
	int		i;
	int		j;
	int		k;
	char	*return_string;

	i = 0;
	j = 0;
	k = 0;
	if (str == NULL)
		return (NULL);
	return_string = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(analyse)
				+ ft_strlen(copy)) + 1);
	while (str[i])
	{
		if (i == indice)
		{
			if (copy)
				while (copy[k])
					return_string[j++] = copy[k++];
			i = i + ft_strlen(analyse) + 1;
		}
		else
			return_string[j++] = str[i++];
	}
	return (return_string[j] = '\0', return_string);
}

char	*dollar_replace_helper(t_minishell *m_s, char *s, int indice, int i)
{
	int		j;
	char	*new_str;
	char	*env_ret;
	char	*analyse;

	j = 0;
	if (i == indice)
	{
		while (s[++i] != ' ' && is_alpha(s[i]) == 1)
			j++;
		analyse = malloc(sizeof(char) * j + 1);
		i = i - j;
		j = 0;
		while (s[i] != ' ' && is_alpha(s[i]) == 1)
			analyse[j++] = s[i++];
		analyse[j] = '\0';
		new_str = ft_strdup(s);
		env_ret = search_env(m_s, analyse);
		new_str = (free(new_str), replacer(s, analyse, env_ret, indice));
		return (free(analyse), free(env_ret), m_s->arg_size = j, new_str);
	}
	return (s);
}

char	*dollar_replace(t_minishell *m_s, char *str, int indice, int *size)
{
	int		i;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		tmp = dollar_replace_helper(m_s, str, indice, i);
		if (new_strcmp(tmp, str) != 0 && tmp != NULL)
		{
			free(str);
			return (tmp);
		}
	}
	(*size) += m_s->arg_size;
	return (str);
}

void	var_increase(int *size, int *i)
{
	(*size)++;
	(*i)++;
}
