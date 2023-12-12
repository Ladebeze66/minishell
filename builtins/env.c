/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:36:35 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 12:10:09 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **args, t_minishell *shell)
{
	int		i;
	char	*env_var;

	(void)args;
	i = 0;
	while (shell->environ[i])
	{
		env_var = shell->environ[i];
		printf("%s\n", env_var);
		i++;
	}
	return (0);
}
