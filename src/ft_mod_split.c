/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:21:01 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/06/09 16:36:02 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_str_word(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && c == s[i])
			i++;
		if (s[i] && c != s[i])
		{
			word++;
			while (s[i] && c != s[i])
				i++;
		}
	}
	return (word);
}

char	*ft_mallocage(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && c != s[i])
		i++;
	tab = (char *)malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && c != s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_mod_split(char const *s, char c)
{
	char	**string;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = ft_str_word(s, c);
	j = 0;
	string = (char **)malloc(sizeof(char *) * (i + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s[j])
	{
		while (s[j] && c == s[j])
			j++;
		if (s[j] && c != s[j])
		{
			string[i++] = ft_mallocage((s + j), c);
			while (s[j] && c != s[j])
				j++;
		}
	}
	string[i] = NULL;
	return (string);
}
