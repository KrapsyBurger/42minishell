/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:36:00 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 13:59:28 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_ex(t_exec **ex)
{
	t_exec	*temp;

	temp = (*ex);
	(*ex) = (*ex)->next;
	(*ex)->cmd = NULL;
	(*ex)->infile = NULL;
	(*ex)->outfile = NULL;
	(*ex)->first = NULL;
	if (temp->heredoc_string == NULL)
		(*ex)->heredoc_string = NULL;
	if (temp->cmd == NULL)
		(*ex)->heredoc_string = NULL;
	else
		(*ex)->heredoc_string = ft_strjoin(temp->heredoc_string, "a");
	(*ex)->heredoc_filename = NULL;
	(*ex)->to_append = 0;
	(*ex)->to_heredoc = 0;
	(*ex)->fd_heredoc = 0;
	(*ex)->fd_rd = 0;
	(*ex)->fd_wr = 1;
	(*ex)->next = NULL;
}

int	list_fill_helper(t_exec **ex, t_tokens **temp, t_minishell *ms)
{
	if (infile_fill(ex, temp) == 1)
		return (1);
	if (outfile_fill(ex, temp) == 1)
		return (1);
	if (cmd_fill(ex, temp, 0) == 1)
		return (1);
	if (heredoc_fill(ex, temp, ms) == 1)
		return (1);
	return (0);
}

int	to_heredoc(t_exec **ex, t_tokens *temp)
{
	int	a;

	a = 0;
	while (temp && temp->next)
	{
		if (new_strcmp(temp->token_type, "stdin_redirect") == 0)
			(*ex)->to_heredoc = 0;
		else if (new_strcmp(temp->token_type, "heredoc") == 0)
		{
			a++;
			(*ex)->to_heredoc = 1;
		}
		temp = temp->next;
	}
	if (a >= 1)
		return (1);
	return (0);
}

char	*parser_strjoin(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (free(s1), str);
	}
	return (NULL);
}
