/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:24:54 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:21:58 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_helper(char *str, int i)
{
	int	quit;
	int	is_dash_n;

	quit = 0;
	is_dash_n = 0;
	while (quit == 0)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '-')
		{
			is_dash_n = 1;
			i++;
			while (str[i] == 'n')
				i++;
		}
		else
			quit = 1;
	}
	if (str[i])
	{
		while (str[i] != '\0')
			write(1, &str[i++], 1);
	}
	return (is_dash_n);
}

void	echo(char *str)
{
	int	i;
	int	is_dash_n;

	i = 0;
	is_dash_n = 0;
	if (str)
	{
		is_dash_n = echo_helper(str, i);
		if (is_dash_n == 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	g_global = 0;
}
