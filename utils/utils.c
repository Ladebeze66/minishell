/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:49:16 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 16:00:03 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_only_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

char	*get_env_value(const char *key, char **environ)
{
	int		i;
	char	*entry;
	char	*delim;

	if (!key || !environ)
		return (NULL);
	i = 0;
	entry = environ[i];
	while (entry != NULL)
	{
		delim = strchr(entry, '=');
		if (delim != NULL)
		{
			if (ft_strncmp(entry, key, delim - entry)
				== 0 && ft_strlen(key) == (size_t)(delim - entry))
				return (delim + 1);
		}
		i++;
		entry = environ[i];
	}
	return (NULL);
}
