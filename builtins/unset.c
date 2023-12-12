/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:15:04 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 12:10:47 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **args, t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	if (args[1] == NULL)
	{
		write(2, RED"minishell: expected argument to \"unset\"\n", 48);
		return (1);
	}
	while (shell->environ[i] != NULL)
	{
		if (ft_strncmp(shell->environ[i], args[1], ft_strlen(args[1]))
			== 0 && shell->environ[i][ft_strlen(args[1])] == '=')
		{
			j = i;
			while (shell->environ[j] != NULL)
			{
				shell->environ[j] = shell->environ[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
	return (0);
}
