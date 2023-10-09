/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:55:47 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 17:37:45 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_there_quote(char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			ret = 1;
		i++;
	}
	return (ret);
}

char	*new_strdup(char **s1, int index_ret)
{
	int		i;
	char	*dup;

	i = 0;
	(*s1)[index_ret] = '\0';
	while ((*s1)[i])
		i++;
	dup = (char *)malloc(sizeof(char) * i + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while ((*s1)[i])
	{
		dup[i] = (*s1)[i];
		i++;
	}
	dup[i] = '\0';
	free(*s1);
	return (dup);
}

void	var_assign(int *index_ret, int *index_s, char **s, char **ret)
{
	(*ret)[*index_ret] = (*s)[*index_s];
	(*index_ret)++;
	(*index_s)++;
}

char	*global_replace(char *s, int i, int *b, char *a)
{
	int		d;
	char	*ret;
	int		index_a;
	int		index_s;

	d = 0;
	index_a = 0;
	index_s = 0;
	a = ft_itoa(g_global);
	ret = malloc(sizeof(char) * ft_strlen(s) + ft_strlen(a) + 1);
	while (index_s != i + 2)
	{
		if (s[index_s] == '$' && s[index_s + 1] == '?')
		{
			while (a[index_a])
				var_assign(&d, &index_a, &a, &ret);
			index_a = 0;
			index_s += 2;
		}
		else
			var_assign(&d, &index_s, &s, &ret);
	}
	while (s[index_s])
		var_assign(&d, &index_s, &s, &ret);
	return (*b += ft_strlen(a) + 1, free(a), free(s), new_strdup(&ret, d));
}

int	is_alpha(char c)
{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
		return (0);
	return (1);
}
