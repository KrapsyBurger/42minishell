/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:30:11 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/25 18:41:00 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sighandler_heredoc(int sig)
{
	char	*cmd[2];

	cmd[0] = ft_strdup("/usr/bin/true");
	cmd[1] = NULL;
	if (sig == SIGINT)
	{
		g_global = 130;
		close_all_fd();
		close(STDERR_FILENO);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		execve("/usr/bin/true", cmd, NULL);
		return ;
	}
}

void	heredoc_child(t_exec **ex, t_minishell *ms, char **cmd, int save_stdout)
{
	cmd[0] = ft_strdup("/usr/bin/false");
	cmd[1] = NULL;
	(void)cmd;
	write(1, "heredoc> ", 9);
	dup2((*ex)->fd_heredoc, STDOUT_FILENO);
	signal(SIGINT, sighandler_heredoc);
	heredoc_helper2(ms, ex);
	close((*ex)->fd_heredoc);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	execve("/usr/bin/false", cmd, NULL);
}

void	heredoc(t_exec **ex, t_minishell *ms)
{
	int		save_stdout;
	pid_t	cpid;
	int		status;
	char	*cmd[2];

	save_stdout = dup(1);
	(*ex)->fd_heredoc = open((*ex)->heredoc_string, O_RDWR
			| O_TRUNC | O_CREAT, 0644);
	cpid = fork();
	signal(SIGINT, SIG_IGN);
	if (cpid == 0)
		heredoc_child(ex, ms, cmd, save_stdout);
	close((*ex)->fd_heredoc);
	close(save_stdout);
	wait(&status);
	if (WIFEXITED(status) == 1)
	{
		if (WEXITSTATUS(status) == 0)
		{
			ms->heredoc_bool = 1;
			g_global = 130;
		}
	}
	signal(SIGINT, sighandler);
}

int	heredoc_free_token(t_tokens **list)
{
	t_tokens	*temp;

	temp = (*list)->next;
	while (temp && temp->next)
	{
		free((*list)->token);
		free((*list)->token_type);
		free((*list));
		(*list) = temp;
		temp = temp->next;
	}
	free(temp);
	free((*list)->token);
	free((*list)->token_type);
	free((*list));
	return (0);
}

int	heredoc_helper3(t_minishell *ms, t_exec **ex)
{
	if (new_strcmp(ms->heredoc_s, ms->heredoc_s2) != 0)
	{
		if (access((*ex)->heredoc_string, W_OK | F_OK) == 0)
		{
			expander_heredoc(&ms->heredoc_s, ms);
			printf("%s", ms->heredoc_s);
			return (0);
		}
		else
			return (free(ms->heredoc_s), free(ms->heredoc_s2),
				write(2, "File not found or permission denied.\n", 38), 38);
	}
	else
		return (38);
}
