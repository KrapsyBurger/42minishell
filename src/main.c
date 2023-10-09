/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:36:44 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 21:00:43 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_global;

int	history_checker(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if ((str[j] < 9 || str[j] > 13) && str[j] != ' ')
			i++;
		j++;
	}
	return (i);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global = 130;
		return ;
	}
	if (sig == SIGQUIT)
		return ;
}

int	main_helper(t_minishell *m_s, t_tokens *token)
{
	int		i;

	while (1)
	{
		token_init(&token);
		m_s->input = readline(" Minishell> ");
		if (m_s->input == NULL)
			return (ctrl_d_exit(m_s, token));
		if (history_checker(m_s->input) > 0)
			add_history(m_s->input);
		if (lexer(m_s->input, &token) == 42)
			return (exit_free_token(&token), free(m_s->input), 130);
		expander(&token, m_s);
		i = exit_checker(&token);
		if (i == 2)
			return (exit_free_token(&token), free(m_s->input), 130);
		else if (i == 5)
			return (exit_return(&token, m_s));
		if (pipex_parser(m_s, &token) == 1)
			return (exit_free_token(&token), free(m_s->input), 130);
		exit_free_token(&token);
		free(m_s->input);
		m_s->heredoc_bool = 0;
	}
	return (0);
}

void	main_forker(pid_t cpid, t_minishell *ms, t_tokens *token)
{
	int	ret;

	if (cpid == 0)
	{
		ret = main_helper(ms, token);
		while (ret == 130)
			ret = main_helper(ms, token);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(ret);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_tokens	*token;
	t_minishell	*ms;
	pid_t		cpid;
	int			ret;

	(void)argc;
	(void)argv;
	g_global = 0;
	ms = malloc(sizeof(t_minishell));
	token = NULL;
	init(ms);
	if (env[0] == NULL)
		no_env(ms);
	else
		yes_env(ms, env);
	cpid = fork();
	if (cpid < 0)
		return (130);
	main_forker(cpid, ms, token);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(cpid, &ret, WCONTINUED);
	ret = WEXITSTATUS(ret);
	demallocage(ms);
	return (ret);
}
