/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:45:14 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 12:23:50 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	create_process(char *path, char **args, char **environ)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, args, environ);
		perror(RED"Command execution failed"RST);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror(RED"Fork failed"RST);
	}
	return (pid);
}

pid_t	execute_external_command(char **args, char **environ)
{
	pid_t	pid;
	char	*path;

	pid = -1;
	if (!args || !args[0])
		return (-1);
	path = find_executable(args[0], environ);
	if (!path)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		perror(RED "Command not found" RST);
		return (-1);
	}
	pid = create_process(path, args, environ);
	if (pid < 0)
	{
		perror(RED"Fork failed"RST);
	}
	free(path);
	return (pid);
}
