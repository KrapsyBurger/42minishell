/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 19:51:52 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:36:00 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_link(t_exec *ex)
{
	int		pipe_fd[2];
	t_exec	*tmp;

	tmp = ex;
	while (tmp->next)
	{
		if (pipe(pipe_fd) == 0)
		{
			tmp->fd_wr = pipe_fd[1];
			tmp->next->fd_rd = pipe_fd[0];
		}
		tmp = tmp->next;
	}
}

void	close_fd(t_exec *ex, int wr, int rd)
{
	t_exec	*tmp;

	tmp = ex;
	while (tmp)
	{
		if (tmp->fd_wr > 2 && tmp->fd_wr != wr)
			close(tmp->fd_wr);
		if (tmp->fd_rd > 2 && tmp->fd_rd != rd)
			close(tmp->fd_rd);
		tmp = tmp->next;
	}
}

void	forkhandler(int sig)
{
	if (sig == SIGINT)
	{
		g_global = 130;
		return ;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit (core dumped)\n", 1);
		return ;
	}
}

int	pipexec_helper(pid_t cpid, t_minishell *m_s, t_exec *tmp, t_tokens *tk)
{
	while (tmp)
	{
		if (tmp->cmd == NULL)
			empty(tmp);
		else if (is_bltn(tmp->cmd[0]) == 0)
			return (bltn_exec(tmp->cmd, m_s, tmp), close_all_fd(), 1);
		else
		{
			signal(SIGINT, forkhandler);
			signal(SIGQUIT, forkhandler);
			cpid = fork();
			if (cpid < 0)
				return (perror("Fork : "), 1);
			if (cpid == 0)
				child(tmp, m_s, tk);
		}
		tmp = tmp->next;
	}
	return (close_all_fd(), 0);
}

void	pipexec(t_minishell *m_s, t_exec *ex, t_tokens *tk)
{
	t_exec	*tmp;
	int		wstatus;
	pid_t	cpid;

	tmp = ex;
	cpid = -1;
	if (m_s->heredoc_bool == 0)
	{
		pipe_link(tmp);
		if (pipexec_helper(cpid, m_s, tmp, tk) == 1)
			return ;
		close_all_fd();
		tmp = ex;
		signal(SIGINT, SIG_IGN);
		while (tmp)
		{
			waitpid(cpid, &wstatus, WCONTINUED);
			if (g_global == 0)
				g_global = WEXITSTATUS(wstatus);
			tmp = tmp->next;
		}
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
	}
}
