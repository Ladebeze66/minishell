/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:58:11 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 19:09:08 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_pipe_token(char *token, t_minishell *shell)
{
	(void)shell;
	return (strcmp(token, "|") == 0);
}

bool	is_redirection_token(char *token)
{
	static const char	*redirections[] = {">", "<", ">>", "<<", NULL};
	int					i;

	i = 0;
	while (redirections[i] != NULL)
	{
		if (ft_strcmp(token, redirections[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_variable_token(char *token)
{
	return (token[0] == '$' && token[1] != '\0');
}

void	add_token_to_command_wrapper(t_command **command, char *token)
{
	if (!*command)
	{
		*command = create_new_command();
	}
	add_token_to_command(*command, token);
}

int	is_variable_resolvable(char *token, t_State current_state)
{
	return ((current_state == DOUBLE_QUOTE || (token[0] == '$'))
		&& (current_state != SINGLE_QUOTE));
}
