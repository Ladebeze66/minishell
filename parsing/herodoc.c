/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herodoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:49:41 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 14:16:55 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_and_write_input(int write_end, const char *delimiter)
{
	char	buffer[1024];
	ssize_t	num_read;
	char	*newline;

	while (1)
	{
		printf("> ");
		fflush(stdout);
		num_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (num_read <= 0)
			break ;
		buffer[num_read] = '\0';
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0)
		{
			newline = ft_strchr(buffer, '\n');
			if (newline != NULL && newline - buffer
				== (ptrdiff_t)ft_strlen(delimiter))
				break ;
		}
		write(write_end, buffer, num_read);
	}
}

static void	child_process(int *pipe_fds, const char *delimiter)
{
	close(pipe_fds[0]);
	read_and_write_input(pipe_fds[1], delimiter);
	close(pipe_fds[1]);
	exit(EXIT_SUCCESS);
}

static void	parent_process(int *pipe_fds)
{
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
}

void	heredoc_input(const char *delimiter)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(pipe_fds, delimiter);
	else
	{
		parent_process(pipe_fds);
		waitpid(pid, NULL, 0);
	}
}
