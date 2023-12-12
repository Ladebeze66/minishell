/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:48:07 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 12:24:31 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_relative_path(const char *cmd)
{
	if (cmd == NULL)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0 || cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*build_full_path(const char *token, const char *cmd)
{
	char	*temp;

	if (cmd == NULL)
		return (NULL);
	temp = malloc(ft_strlen(token) + ft_strlen(cmd) + 2);
	if (temp == NULL)
		return (NULL);
	ft_strcpy(temp, token);
	ft_strcat(temp, "/");
	ft_strcat(temp, cmd);
	return (temp);
}

static char	*search_path(char *path, const char *cmd)
{
	char	*path_copy;
	char	*token;
	char	*temp;
	char	*full_path;

	if (cmd == NULL)
		return (NULL);
	full_path = NULL;
	path_copy = ft_strdup(path);
	token = ft_strtok(path_copy, ":");
	while (token != NULL)
	{
		temp = build_full_path(token, cmd);
		if (temp && access(temp, X_OK) == 0)
		{
			full_path = ft_strdup(temp);
			free(temp);
			break ;
		}
		free(temp);
		token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (full_path);
}

char	*find_executable(const char *cmd, char **environ)
{
	char	*path;
	char	*relative_path_check;
	char	*full_path;

	if (cmd == NULL)
		return (NULL);
	relative_path_check = check_relative_path(cmd);
	if (relative_path_check != NULL)
		return (relative_path_check);
	path = get_env_value("PATH", environ);
	if (!path || ft_strlen(path) == 0)
		return (NULL);
	full_path = search_path(path, cmd);
	return (full_path);
}
