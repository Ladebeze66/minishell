/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:21:23 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 18:55:48 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin_and_free(char **args, t_minishell *shell, int fd)
{
	int	status;

	if (ft_strcmp(args[0], "echo") == 0)
	{
		status = builtin_echo(args, shell, fd);
	}
	else
	{
		status = execute_builtin(args, shell);
	}
	free_args_array(args);
	shell->last_exit_status = status;
	return (status);
}

static int	execute_external_and_free(char **args, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = execute_external_command(args, shell->environ);
	free_args_array(args);
	if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
		{
			shell->last_exit_status = WEXITSTATUS(status);
		}
	}
	else
	{
		shell->last_exit_status = 127;
	}
	return (status);
}

static int	process_command(t_command *command, t_minishell *shell, int fd)
{
	char	**args;
	int		status;

	status = 0;
	args = build_args_array(command);
	if (args != NULL)
	{
		if (is_builtin_command(command->command, shell))
		{
			status = execute_builtin_and_free(args, shell, fd);
		}
		else
		{
			status = execute_external_and_free(args, shell);
		}
	}
	return (status);
}

void	execute_command(t_command *command, t_minishell *shell, int fd)
{
	if (command == NULL || command->command == NULL)
	{
		return ;
	}
	process_command(command, shell, fd);
}
