/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfascia <nathanfascia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:22:51 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/24 22:58:35 by nfascia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	infile_checker(char	**infile)
{
	int	i;
	int	final_infile;
	int	last_valid;

	i = 0;
	if (infile == NULL)
		return (-2);
	while (infile[i] != NULL)
	{
		if (access(infile[i], R_OK) == 0)
		{
			last_valid = i;
			i++;
		}
		else
			return (ft_puterror("Minishell: no such file or directory: ",
					infile[i], "\n"), g_global = 1, -1);
	}
	final_infile = open(infile[last_valid], O_RDONLY);
	return (final_infile);
}

int	outfile_checker(t_exec *ex, char **outfile)
{
	int	i;
	int	final_outfile;

	i = 0;
	final_outfile = 1;
	if (outfile == NULL)
		return (-2);
	while (outfile[i] != NULL)
	{
		if (ex->to_append == 1)
			final_outfile = open(outfile[i], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			final_outfile = open(outfile[i], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (final_outfile == -1)
			return (ft_puterror("Minishell: permission denied: ",
					outfile[i], "\n"), g_global = 1, -1);
		i++;
	}
	return (final_outfile);
}
