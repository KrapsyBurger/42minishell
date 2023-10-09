/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:02 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:55:19 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pipex_parser(t_exec *ex)
{
	ex->cmd = NULL;
	ex->infile = NULL;
	ex->outfile = NULL;
	ex->first = NULL;
	ex->heredoc_filename = NULL;
	ex->fd_heredoc = 0;
	ex->to_heredoc = 0;
	ex->to_append = 0;
	ex->fd_rd = 0;
	ex->fd_wr = 1;
	ex->next = NULL;
}

int	pipex_parser(t_minishell *m_s, t_tokens **tk)
{
	t_exec		*ex;
	t_tokens	*temp;
	t_exec		*temp_ex;

	ex = malloc(sizeof(t_exec));
	temp = (*tk);
	if (to_heredoc(&ex, temp) == 1)
		ex->heredoc_string = ft_strdup("fzbxh8mxfn");
	else
		ex->heredoc_string = NULL;
	init_pipex_parser(ex);
	temp_ex = ex;
	if (list_fill(&temp_ex, &temp, m_s) == 1)
	{
		ft_putstr_fd("Syntax error.\n", 2);
		g_global = 2;
		free_exec(&ex);
		return (1);
	}
	pipexec(m_s, ex, (*tk));
	free_exec(&ex);
	return (0);
}
