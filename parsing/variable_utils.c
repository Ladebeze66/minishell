/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:46:07 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 14:11:44 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*skip_dollar(const char *variable_name)
{
	if (variable_name[0] == '$')
		return (variable_name + 1);
	return (variable_name);
}

void	reverse_str(char *str, int length)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

char	*search_env_variable(const char *name_to_search, t_minishell *shell)
{
	int		i;
	char	*env_entry;
	size_t	name_len;

	name_len = ft_strlen(name_to_search);
	i = 0;
	while (shell->environ[i])
	{
		env_entry = shell->environ[i];
		if (ft_strncmp(env_entry, name_to_search, name_len) == 0
			&& env_entry[name_len] == '=')
			return (ft_strdup(env_entry + name_len + 1));
		i++;
	}
	return (ft_strdup(""));
}
