/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:50:42 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/24 22:28:26 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	bltn_infile(t_exec *tmp)
{
	int	buff;

	buff = infile_checker(tmp->infile);
	if (buff == -1)
	{
		g_global = 1;
		return (-1);
	}
	if (buff != -2)
	tmp->fd_rd = buff;
	return (0);
}

int	bltn_infile_heredoc(t_exec *tmp)
{
	int	buff;

	if (tmp->to_heredoc == 1)
	{
		buff = infile_checker(tmp->infile);
		if (buff == -1)
		{
			g_global = 1;
			return (-1);
		}
		if (buff != -2)
			close(buff);
		tmp->fd_rd = tmp->fd_heredoc;
	}
	else
		return (bltn_infile(tmp));
	return (0);
}

int	bltn_outfile(t_exec *tmp)
{
	int	buff;

	buff = outfile_checker(tmp, tmp->outfile);
	if (buff == -1)
	{
		g_global = 1;
		return (-1);
	}
	if (buff != -2)
		tmp->fd_wr = buff;
	return (0);
}

void	bltn_exec(char **cmd, t_minishell *m_s, t_exec *tmp)
{
	int		saved_in;
	int		saved_out;

	if (bltn_infile_heredoc(tmp) != 0)
		return ;
	if (bltn_outfile(tmp) != 0)
		return ;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (tmp->fd_rd != 0)
	{
		dup2(tmp->fd_rd, STDIN_FILENO);
		close(tmp->fd_rd);
	}
	if (tmp->fd_wr != 1)
	{
		dup2(tmp->fd_wr, STDOUT_FILENO);
		close (tmp->fd_wr);
	}
	bltn_select(cmd, m_s);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
}
