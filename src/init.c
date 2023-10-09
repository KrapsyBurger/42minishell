/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:14 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 20:26:56 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(t_minishell *m_s)
{
	m_s->heredoc_bool = 0;
	m_s->input = NULL;
	m_s->og_env = NULL;
	m_s->new_env = NULL;
	m_s->lst_env = NULL;
	m_s->heredoc_s = NULL;
	m_s->heredoc_s2 = NULL;
	ft_memset(&m_s->termios, 0, sizeof(struct termios));
	tcgetattr(0, &m_s->termios);
	m_s->termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &m_s->termios);
}

void	init_exec(t_exec **ex, t_tokens *temp)
{
	(*ex)->cmd = NULL;
	(*ex)->infile = NULL;
	(*ex)->outfile = NULL;
	(*ex)->first = NULL;
	if (to_heredoc(ex, temp) == 1)
		(*ex)->heredoc_string = ft_strdup("fzbxh8mxfn");
	else
		(*ex)->heredoc_string = NULL;
	(*ex)->heredoc_filename = NULL;
	(*ex)->fd_heredoc = 0;
	(*ex)->to_heredoc = 0;
	(*ex)->to_append = 0;
	(*ex)->fd_rd = 0;
	(*ex)->fd_wr = 1;
	(*ex)->next = NULL;
}

void	token_init(t_tokens **token)
{
	(*token) = malloc(sizeof(t_tokens));
	(*token)->token = NULL;
	(*token)->token_type = NULL;
	(*token)->next = NULL;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}
