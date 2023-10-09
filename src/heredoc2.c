/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:13:31 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 12:56:59 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_final_substr(char *s, int start, int len)
{
	char			*a;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	a = NULL;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = (ft_strlen(s + start));
	a = malloc(sizeof(char) * len + 1);
	if (a == NULL)
		return (a);
	a = ft_a(a, s, len, start);
	gnl_free((char *)s);
	return (a);
}

char	*new_strjoin(char *s1, char *s2)
{
	char			*a;
	unsigned long	i;
	unsigned long	j;

	if (s1 == NULL || s2 == NULL)
		return (ft_strdup(""));
	a = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	if (a == NULL)
		return (a);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
	return (a);
}

char	*get_next_line(int fd)
{
	int				i;
	char			buff[1];
	char			*result;
	static char		*line = NULL;

	while (ft_is_newline(line, '\n') != 1)
	{
		i = read(fd, buff, 1);
		if (ft_strlen(line) > 0 && i == 0)
		{
			result = gnl_substr(line, 0, ft_strlen(line));
			line = gnl_free(line);
			return (result);
		}	
		else if (i == -1 || i == 0)
			return (gnl_free(line));
		line = gnl_strjoin(line, buff, i);
	}
	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	result = gnl_substr(line, 0, i + 1);
	line = ft_final_substr(line, i + 1, ft_strlen(line));
	return (result);
}

void	expander_heredoc(char **s, t_minishell *ms)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '$' && (*s)[i + 1] == '?')
			(*s) = global_replace((*s), i, &size, NULL);
		else if ((*s)[i] == '$')
		{
			(*s) = dollar_replace(ms, (*s), i, &size);
			if ((*s) == NULL)
				break ;
		}
		i++;
	}
}

int	heredoc_helper2(t_minishell *ms, t_exec **ex)
{
	ms->heredoc_s = get_next_line(0);
	ms->heredoc_s2 = ft_strjoin((*ex)->heredoc_filename, "\n");
	if (ms->heredoc_s == NULL)
		return (g_global = 0, free(ms->heredoc_s), free(ms->heredoc_s2), 0);
	if (heredoc_helper3(ms, ex) == 38)
		return (0);
	while (new_strcmp(ms->heredoc_s, ms->heredoc_s2) != 0 && g_global != 42)
	{
		free(ms->heredoc_s);
		ms->heredoc_s = get_next_line(0);
		if (ms->heredoc_s == NULL)
			return (g_global = 0, free(ms->heredoc_s), free(ms->heredoc_s2), 0);
		if (new_strcmp(ms->heredoc_s, ms->heredoc_s2) != 0)
		{
			if (access((*ex)->heredoc_string, W_OK | F_OK) == 0)
			{
				expander_heredoc(&ms->heredoc_s, ms);
				printf("%s", ms->heredoc_s);
			}
			else
				return (free(ms->heredoc_s), free(ms->heredoc_s2),
					write(2, "File not found or permission denied.\n", 38));
		}
	}
	return (free(ms->heredoc_s), free(ms->heredoc_s2), 0);
}
