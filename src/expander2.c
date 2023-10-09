/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:02:27 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 21:01:15 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_quote(char **s, int *index_s, int *index_ret, char **ret)
{
	(*index_s)++;
	while ((*s)[(*index_s)] != '"')
	{
		(*ret)[(*index_ret)] = (*s)[(*index_s)];
		(*index_ret)++;
		(*index_s)++;
	}
	(*index_s)++;
}

void	simple_quote(char **s, int *index_s, int *index_ret, char **ret)
{
	(*index_s)++;
	while ((*s)[(*index_s)] != '\'')
	{
		(*ret)[(*index_ret)] = (*s)[(*index_s)];
		(*index_ret)++;
		(*index_s)++;
	}
	(*index_s)++;
}

char	*trim_quote(char *s, int size)
{
	char	*ret;
	int		index_ret;
	int		index_s;

	index_ret = 0;
	index_s = 0;
	if (is_there_quote(s) == 0)
		return (s);
	ret = malloc(sizeof(char) * size + 1);
	while (s[index_s])
	{
		if (s[index_s] == '"')
			double_quote(&s, &index_s, &index_ret, &ret);
		else if (s[index_s] == '\'')
			simple_quote(&s, &index_s, &index_ret, &ret);
		if (s[index_s] != '"' && s[index_s] != '\'')
		{
			if (s[index_s] == '\0')
				break ;
			ret[index_ret] = s[index_s];
			var_increase(&index_ret, &index_s);
		}
	}
	ret[index_ret] = '\0';
	return (free(s), ret);
}

void	expander_helper(t_minishell *m_s, t_tokens **a, int i, int size)
{
	while ((*a) && (*a)->token && (*a)->token[i])
	{
		if ((*a)->token[i] == '"')
			expander_helper2(m_s, a, &i, &size);
		else if ((*a)->token[i] == '$' && (*a)->token[i + 1] == '?')
			(*a)->token = global_replace((*a)->token, i, &size, NULL);
		else if ((*a)->token[i] == '$')
		{
			(*a)->token = dollar_replace(m_s, (*a)->token, i, &size);
			if ((*a)->token == NULL || (*a)->token[i] == 0)
				break ;
		}
		else if ((*a)->token[i] == '\'')
		{
			i++;
			while ((*a)->token[i] != '\'')
				var_increase(&i, &size);
		}
		var_increase(&i, &size);
	}
	expander_helper3(a, size);
}

void	expander(t_tokens **token, t_minishell *m_s)
{
	t_tokens	*temp;

	temp = (*token);
	while (temp && temp->next)
	{
		expander_helper(m_s, &temp, 0, 0);
		if (new_strcmp(temp->token_type, "filename double quote") == 0
			|| new_strcmp(temp->token_type, "filename single quote") == 0
			|| new_strcmp(temp->token_type, "echo filename") == 0
			|| new_strcmp(temp->token_type, "echo cmd") == 0)
		{
			free(temp->token_type);
			temp->token_type = ft_strdup("filename");
		}
		if (new_strcmp(temp->token_type, "heredoc") == 0)
		{
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
