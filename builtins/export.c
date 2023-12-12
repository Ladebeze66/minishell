/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:20:32 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 12:11:19 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_env(char **env, int env_size)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (i < env_size)
	{
		name = extract_name(env[i]);
		value = extract_value(env[i]);
		if (value)
		{
			printf("declare -x %s=\"%s\"\n", name, value);
			free(value);
		}
		else
		{
			printf("declare -x %s\n", name);
		}
		free(name);
		i++;
	}
}

static void	print_sorted_env(t_minishell *shell)
{
	int		env_size;
	char	**sorted_env;

	env_size = count_env_vars(shell->environ);
	sorted_env = copy_env(shell->environ, env_size);
	if (!sorted_env)
		return ;
	sort_env(sorted_env, env_size);
	print_env(sorted_env, env_size);
	free(sorted_env);
}

int	builtin_export(char **args, t_minishell *shell)
{
	if (args[1] == NULL)
	{
		print_sorted_env(shell);
		return (0);
	}
	else
	{
		return (export_set_env(args, shell));
	}
}
