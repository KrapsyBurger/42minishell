/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:32:32 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/24 16:58:02 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile(t_exec *tmp)
{
	int	buff;

	buff = infile_checker(tmp->infile);
	if (buff == -1)
	{
		g_global = 1;
		exit(1);
	}
	if (buff != -2)
		tmp->fd_rd = buff;
}

void	outfile(t_exec *tmp, t_minishell *m_s, t_tokens *tk)
{
	int	buff;

	buff = outfile_checker(tmp, tmp->outfile);
	if (buff == -1)
	{
		g_global = 1;
		exit_free_token(&tk);
		ft_envclear(&m_s->lst_env);
		free_array(m_s->new_env);
		free(m_s);
		free_exec(&tmp);
		close(STDERR_FILENO);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(1);
	}
	if (buff != -2)
		tmp->fd_wr = buff;
}

void	infile_heredoc(t_exec *tmp, t_minishell *m_s, t_tokens *tk)
{
	int	buff;

	if (tmp->to_heredoc == 1)
	{
		buff = infile_checker(tmp->infile);
		if (buff == -1)
			return ;
		if (access(tmp->heredoc_string, F_OK | R_OK) == 0)
			buff = open(tmp->heredoc_string, O_RDONLY);
		else
		{
			exit_free_token(&tk);
			ft_envclear(&m_s->lst_env);
			free_array(m_s->new_env);
			free(m_s);
			free_exec(&tmp);
			exit(1);
		}
		tmp->fd_rd = buff;
	}
	else
		infile(tmp);
	outfile(tmp, m_s, tk);
}

void	dup_checker(t_exec *tmp)
{
	if (tmp->fd_rd != 0)
	{
		dup2(tmp->fd_rd, STDIN_FILENO);
		close(tmp->fd_rd);
	}
	if (tmp->fd_wr != 1)
	{
		dup2(tmp->fd_wr, STDOUT_FILENO);
		close(tmp->fd_wr);
	}
	close_all_fd();
}
