/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:00:24 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 19:25:39 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_and_free_tree(t_command_node *root,
			t_minishell *shell, int command_count, int fd)
{
	if (root)
	{
		execute_command_tree(root, shell, command_count, fd);
		free_command_tree(root);
	}
}

int	check_syntax_error(char **tokens, int token_index,
		bool in_quotes, t_minishell *shell)
{
	if (in_quotes)
	{
		return (0);
	}
	if (is_redirection_token(tokens[token_index])
		|| is_pipe_token(tokens[token_index], shell))
	{
		if (token_index == 0 || tokens[token_index + 1] == NULL)
		{
			write(2, RED"bash: erreur de syntaxe près du symbole inattendu "
				RST, 58);
			write(2, tokens[token_index], ft_strlen(tokens[token_index]));
			write(2, "\n", 1);
			return (1);
		}
	}
	return (0);
}
