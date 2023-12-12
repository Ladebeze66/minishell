/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:51:11 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 14:06:48 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **args, t_minishell *shell)
{
	(void)shell;
	if (args[1] == NULL)
	{
		write(2, RED"minishell: expected argument to \"cd\"\n"RST, 44);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror(RED"minishell"RST);
		}
	}
	return (0);
}

int	builtin_exit(char **args, t_minishell *shell)
{
	long	exit_code;
	char	*endptr;
	char	*error_message;

	(void)shell;
	if (args[1])
	{
		errno = 0;
		exit_code = strtol(args[1], &endptr, 10);
		if ((errno == ERANGE && (exit_code == LONG_MAX
					|| exit_code == LONG_MIN)) || (errno != 0 && exit_code == 0)
			|| (*endptr != '\0')
			|| (exit_code < 0 || exit_code > 255))
		{
			error_message = "bash: exit: ";
			write(STDERR_FILENO, error_message, strlen(error_message));
			write(STDERR_FILENO, args[1], strlen(args[1]));
			error_message = ": numeric argument required\n";
			write(STDERR_FILENO, error_message, strlen(error_message));
			return (1);
		}
		exit((int)exit_code);
	}
	exit(0);
}

int	builtin_pwd(char **args, t_minishell *shell)
{
	char	cwd[1024];

	(void)shell;
	(void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror(RED"minishell"RST);
	}
	return (0);
}

int	num_builtins(t_minishell *shell)
{
	int	count;

	count = 0;
	while (shell->builtin_str[count])
	{
		count++;
	}
	return (count);
}

int	execute_builtin(char **args, t_minishell *shell)
{
	int	i;
	int	exit_status;

	if (!args || !shell || !shell->builtin_str || !shell->builtin_func)
		return (-1);
	if (!args[0])
	{
		write(2, RED"Command not found: No such file or directory\n", 52);
		return (-1);
	}
	i = 0;
	while (i < num_builtins(shell))
	{
		if (shell->builtin_str[i] && ft_strcmp(args[0],
				shell->builtin_str[i]) == 0)
		{
			if (shell->builtin_func[i])
			{
				exit_status = (*shell->builtin_func[i])(args, shell);
				return (exit_status);
			}
		}
		i++;
	}
	return (-1);
}
