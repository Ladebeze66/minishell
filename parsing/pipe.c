/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:21:38 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 19:21:39 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_and_handle_processes(t_process_params *params)
{
	int						i;
	pid_t					pid;
	t_child_process_params	child_params;

	i = 0;
	while (i < params->command_count)
	{
		pid = fork();
		if (pid == 0)
		{
			child_params = (t_child_process_params){i, params->pipe_fds,
				params->command_count, params->fd,
				params->commands, params->shell};
			setup_child_process(&child_params);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	initialize_pipes(int *pipe_fds, int command_count)
{
	int	i;

	i = 0;
	while (i < command_count - 1)
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	wait_for_all_processes(int command_count)
{
	int	i;

	i = 0;
	while (i < command_count)
	{
		wait(NULL);
		i++;
	}
}

void	process_pipe(t_command **commands,
			t_minishell *shell, int command_count, int fd)
{
	int					*pipe_fds;
	t_process_params	params;

	if (command_count == 1)
	{
		execute_command(commands[0], shell, fd);
		return ;
	}
	pipe_fds = malloc(2 * (command_count - 1) * sizeof(int));
	if (!pipe_fds)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	initialize_pipes(pipe_fds, command_count);
	params = (t_process_params){pipe_fds, commands, shell, command_count, fd};
	create_and_handle_processes(&params);
	close_all_pipes(pipe_fds, 2 * (command_count - 1));
	wait_for_all_processes(command_count);
	free(pipe_fds);
}
