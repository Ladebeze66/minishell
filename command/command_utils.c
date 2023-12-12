/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:03:59 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 12:21:17 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command(t_command *command)
{
	int	i;

	if (!command)
		return ;
	free(command->command);
	if (command->args)
	{
		i = 0;
		while (i < command->arg_count)
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
}

void	reset_command(t_command *command)
{
	if (!command)
		return ;
	free_command(command);
	command->command = NULL;
	command->args = NULL;
	command->arg_count = 0;
}

t_command	*create_new_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	new_command->command = NULL;
	new_command->args = NULL;
	new_command->arg_count = 0;
	return (new_command);
}

void	add_token_to_command(t_command *command, char *token)
{
	char	**new_args;
	char	*new_token;

	if (!token || *token == '\0' || !command)
		return ;
	new_token = ft_strdup(token);
	if (!new_token)
		return ;
	if (command->command == NULL)
		command->command = new_token;
	else
	{
		new_args = ft_realloc(command->args,
				sizeof(char *) * (command->arg_count + 2),
				sizeof(char *) * command->arg_count);
		if (!new_args)
		{
			free(new_token);
			return ;
		}
		command->args = new_args;
		command->args[command->arg_count++] = new_token;
		command->args[command->arg_count] = NULL;
	}
}
