/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:26:09 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 15:01:53 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_env_entry(char **args)
{
	char	*new_env_entry;
	char	*name;
	char	*value;

	name = ft_strtok(args[1], "=");
	value = ft_strtok(NULL, "");
	if (name == NULL || value == NULL)
	{
		write(2, RED"minishell: invalid format for export. "
			"Use NAME=\"value\".\n"RST, 63);
		return (NULL);
	}
	new_env_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_env_entry)
	{
		exit(EXIT_FAILURE);
	}
	ft_strcpy(new_env_entry, name);
	ft_strcat(new_env_entry, "=");
	ft_strcat(new_env_entry, value);
	return (new_env_entry);
}

int	add_new_env_entry(t_minishell *shell, char *new_env_entry)
{
	int		env_size;
	size_t	oldsize;

	env_size = 0;
	oldsize = 0;
	while (shell->environ[env_size] != NULL)
	{
		env_size++;
	}
	oldsize = (env_size + 1) * sizeof(char *);
	shell->environ = ft_reallocarray(shell->environ, env_size + 2,
			sizeof(char *), oldsize);
	if (!shell->environ)
	{
		perror(RED"minishell: error reallocating environment"RST);
		free(new_env_entry);
		return (1);
	}
	shell->environ[env_size] = new_env_entry;
	shell->environ[env_size + 1] = NULL;
	return (0);
}

int	replace_env_entry(t_minishell *shell, char *new_env_entry)
{
	int		i;
	size_t	name_length;

	i = 0;
	name_length = ft_strchr(new_env_entry, '=') - new_env_entry;
	while (shell->environ[i] != NULL)
	{
		if (ft_strncmp(shell->environ[i], new_env_entry, name_length) == 0)
		{
			free(shell->environ[i]);
			shell->environ[i] = new_env_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	update_env(t_minishell *shell, char *new_env_entry)
{
	if (replace_env_entry(shell, new_env_entry) == 0)
	{
		return (add_new_env_entry(shell, new_env_entry));
	}
	return (0);
}

int	export_set_env(char **args, t_minishell *shell)
{
	char	*new_env_entry;

	new_env_entry = create_env_entry(args);
	if (new_env_entry == NULL)
		return (0);
	return (update_env(shell, new_env_entry));
}
