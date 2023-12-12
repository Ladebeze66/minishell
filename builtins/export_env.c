/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:49:41 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 12:19:27 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env_vars(char **environ)
{
	int	count;

	count = 0;
	while (environ[count])
		count++;
	return (count);
}

char	**copy_env(char **environ, int env_size)
{
	char	**env_copy;
	int		i;

	env_copy = malloc((env_size + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < env_size)
	{
		env_copy[i] = environ[i];
		i++;
	}
	env_copy[env_size] = NULL;
	return (env_copy);
}

void	sort_env(char **env, int env_size)
{
	int		sorted;
	int		i;
	char	*temp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < env_size - 1)
		{
			if (strcmp(env[i], env[i + 1]) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}
