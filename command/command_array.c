/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:26:25 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 18:56:21 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**allocate_args_array(t_command *command)
{
	char	**args;

	args = malloc(sizeof(char *) * (command->arg_count + 2));
	if (!args)
	{
		return (NULL);
	}
	return (args);
}

static int	duplicate_command_arg(char **args, t_command *command, int i)
{
	args[i + 1] = ft_strdup(command->args[i]);
	if (!args[i + 1])
	{
		while (--i >= 0)
			free(args[i + 1]);
		free(args[0]);
		free(args);
		return (0);
	}
	return (1);
}

char	**build_args_array(t_command *command)
{
	char	**args;
	int		i;

	args = allocate_args_array(command);
	if (!args)
		return (NULL);
	args[0] = ft_strdup(command->command);
	if (!args[0])
	{
		free(args);
		return (NULL);
	}
	i = 0;
	while (i < command->arg_count)
	{
		if (!duplicate_command_arg(args, command, i))
			return (NULL);
		i++;
	}
	args[command->arg_count + 1] = NULL;
	return (args);
}

void	free_args_array(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}
