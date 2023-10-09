/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:27:36 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:29:59 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_error(t_minishell *m_s, t_tokens *tk, int i, t_exec *tmp)
{
	if (i == 127)
		ft_puterror("Minishell: command not found: ", tmp->first, "\n");
	else if (i == 126)
		ft_puterror("Minishell: permission denied: ", tmp->first, "\n");
	exit_free_token(&tk);
	ft_envclear(&m_s->lst_env);
	free_array(m_s->new_env);
	free(m_s);
	free_exec(&tmp);
	close_all_fd();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(i);
}

void	child(t_exec *tmp, t_minishell *m_s, t_tokens *tk)
{
	int	i;

	infile_heredoc(tmp, m_s, tk);
	dup_checker(tmp);
	if (tmp->cmd[0] != NULL)
	{
		i = command_checker(m_s, tmp, tmp->cmd[0]);
		if (i == 1)
			execve(tmp->first, tmp->cmd, m_s->new_env);
		else if (i == 0)
			child_error(m_s, tk, 127, tmp);
		else
			child_error(m_s, tk, 126, tmp);
	}
	else
		child_error(m_s, tk, 0, tmp);
}
