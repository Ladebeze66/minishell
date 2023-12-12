/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:16:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 18:45:08 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(int *pipe_fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipe_fds[i]);
		i++;
	}
}

void	setup_child_process(t_child_process_params *params)
{
	if (params->i != 0)
	{
		dup2(params->pipe_fds[(params->i - 1) * 2], STDIN_FILENO);
	}
	if (params->i != params->command_count - 1)
	{
		dup2(params->pipe_fds[params->i * 2 + 1], STDOUT_FILENO);
	}
	close_all_pipes(params->pipe_fds, 2 * (params->command_count - 1));
	execute_command(params->commands[params->i], params->shell, params->fd);
	exit(EXIT_SUCCESS);
}
