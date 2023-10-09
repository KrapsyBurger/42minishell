/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:42:09 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 13:58:22 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty(t_exec *tmp)
{
	int	buff;

	buff = infile_checker(tmp->infile);
	if (buff == -1)
		g_global = 1;
	if (buff != -2)
		tmp->fd_rd = buff;
	buff = outfile_checker(tmp, tmp->outfile);
	if (buff == -1)
		g_global = 1;
	if (buff != -2)
		tmp->fd_wr = buff;
	close_fd(tmp, -1, -1);
	g_global = 0;
}
