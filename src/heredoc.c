/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:11:55 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/08 20:49:10 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*gnl_free(char *line)
{
	free(line);
	line = NULL;
	return (NULL);
}

char	*ft_a(char *a, char *s, unsigned long l, unsigned int b)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= b && j < l)
		{
			a[j] = s[i];
			j++;
		}
		i++;
	}
	a[j] = '\0';
	if (a[0] == '\0')
	{
		free(a);
		return (NULL);
	}
	return (a);
}

char	*gnl_substr(char *s, unsigned int start, int len)
{
	char			*a;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	a = NULL;
	if (s == NULL)
		return (NULL);
	if ((int) start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = (ft_strlen(s + start));
	a = malloc(sizeof(char) * len + 1);
	if (a == NULL)
		return (a);
	a = ft_a(a, s, len, start);
	return (a);
}

char	*gnl_strjoin(char *s1, char *s2, int b)
{
	char			*a;
	unsigned long	i;
	unsigned long	j;

	if (s1 == NULL)
		s1 = ft_strdup("");
	if (!s2 || !s1)
		return (NULL);
	s2[b] = '\0';
	a = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = -1;
	j = -1;
	if (a == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		a[i] = s1[i];
	while (s2[++j] != '\0')
	{
		a[i] = s2[j];
		i++;
	}
	gnl_free(s1);
	a[i] = '\0';
	return (a);
}

int	ft_is_newline(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}
