/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demallocage2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:06:41 by nfascia           #+#    #+#             */
/*   Updated: 2022/08/24 22:54:42 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all_fd(void)
{
	int	i;

	i = 2;
	while (++i < 1024)
		close(i);
}

void	free_exec2(t_exec **ex, int *nb, t_exec **temp, char **filename)
{
	if ((*temp)->first != NULL)
		free((*temp)->first);
	if ((*temp)->heredoc_string != NULL)
		free((*temp)->heredoc_string);
	if ((*temp)->heredoc_filename != NULL)
		free((*temp)->heredoc_filename);
	if ((*temp)->cmd != NULL)
		free_array((*temp)->cmd);
	if ((*temp)->infile != NULL)
		free_array((*temp)->infile);
	if ((*temp)->outfile != NULL)
		free_array((*temp)->outfile);
	free((*temp));
	free((*filename));
	if ((*nb) > 0)
		free(*ex);
}

void	free_exec3(int *nb, t_exec **temp, char **filename)
{
	(*filename) = parser_strjoin((*filename), "a");
	unlink((*filename));
	if ((*temp)->first != NULL)
		free((*temp)->first);
	if ((*temp)->heredoc_string != NULL)
		free((*temp)->heredoc_string);
	if ((*temp)->heredoc_filename != NULL)
		free((*temp)->heredoc_filename);
	if ((*temp)->cmd != NULL)
		free_array((*temp)->cmd);
	if ((*temp)->infile != NULL)
		free_array((*temp)->infile);
	if ((*temp)->outfile != NULL)
		free_array((*temp)->outfile);
	(*temp) = (*temp)->next;
	(*nb)++;
}

int	free_exec(t_exec **ex)
{
	t_exec	*temp;
	char	*filename;
	int		nb;

	temp = (*ex);
	filename = ft_strdup("./fzbxh8mxfn");
	unlink(filename);
	nb = 0;
	while (temp && temp->next)
	{
		free_exec3(&nb, &temp, &filename);
	}
	free_exec2(ex, &nb, &temp, &filename);
	return (0);
}

int	ctrl_d_exit(t_minishell *m_s, t_tokens *token)
{
	printf("exit\n");
	free_array(m_s->new_env);
	ft_envclear(&m_s->lst_env);
	exit_free_token(&token);
	free(m_s);
	return (0);
}
