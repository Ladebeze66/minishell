/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:33:11 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/08 23:02:49 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_name(char *env_entry)
{
	int		len;
	char	*name;

	len = 0;
	while (env_entry[len] && env_entry[len] != '=')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, env_entry, len);
	name[len] = '\0';
	return (name);
}

char	*extract_value(char *env_entry)
{
	int		i;
	char	*value;

	i = 0;
	while (env_entry[i] && env_entry[i] != '=')
		i++;
	if (!env_entry[i])
		return (NULL);
	value = ft_strdup(&env_entry[i + 1]);
	return (value);
}

int	builtin_echo_wrapper(char **args, t_minishell *shell)
{
	return (builtin_echo(args, shell, STDOUT_FILENO));
}
