/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:27:30 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 18:57:20 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_option(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **args, t_minishell *shell, int fd)
{
	int		i;
	int		newline;
	char	*output;

	i = 1;
	newline = 1;
	(void)shell;
	if (args[i] != NULL && check_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		output = args[i];
		write(fd, output, ft_strlen(output));
		if (args[i + 1] != NULL)
		{
			write(fd, " ", 1);
		}
		i++;
	}
	if (newline)
		write(fd, "\n", 1);
	return (0);
}
