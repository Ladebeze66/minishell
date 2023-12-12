/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:03:27 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 14:00:23 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	finalize_command(t_command **current_command, t_command_node **root)
{
	t_command_node	*new_node;

	if (*current_command && (*current_command)->command)
	{
		new_node = create_command_node(*current_command);
		add_node_to_tree(root, new_node);
	}
	else if (*current_command)
	{
		free_command(*current_command);
	}
}

static bool	handle_syntax_error_and_free(t_process_token_params *params,
				t_minishell *shell)
{
	char	*current_token;
	bool	sb;

	current_token = params->tokens[*params->token_index];
	sb = shell->tokenizer->symbol;
	if (sb && (is_pipe_token(current_token, shell)
			|| is_redirection_token(current_token)))
	{
		if (check_syntax_error(params->tokens,
				*params->token_index, shell->tokenizer->in_quotes, shell))
		{
			if (*(params->current_command) != NULL)
			{
				free_command(*(params->current_command));
				*(params->current_command) = NULL;
			}
			return (true);
		}
	}
	return (false);
}

static void	process_single_token(t_process_token_params *params,
				t_minishell *shell, int fd)
{
	char	*current_token;

	current_token = params->tokens[*params->token_index];
	if (shell->tokenizer->symbol && (is_pipe_token(current_token, shell)
			|| is_redirection_token(current_token)))
	{
		handle_pipe_and_redirection(params, fd);
	}
	else
	{
		handle_variable_and_other_tokens(params);
	}
}

static void	process_tokens(t_process_token_params *params,
			t_minishell *shell, int fd)
{
	while (params->tokens[*params->token_index] != NULL)
	{
		if (handle_syntax_error_and_free(params, shell))
		{
			return ;
		}
		process_single_token(params, shell, fd);
		(*params->token_index)++;
	}
}

void	parse_tokens(char **tokens, t_minishell *shell, int fd)
{
	t_command_node			*root;
	t_command				*current_command;
	int						token_index;
	int						error_detected;
	t_process_token_params	params;

	token_index = 0;
	current_command = NULL;
	root = NULL;
	error_detected = 0;
	params.tokens = tokens;
	params.token_index = &token_index;
	params.current_command = &current_command;
	params.root = &root;
	params.shell = shell;
	params.command_count = 1;
	process_tokens(&params, shell, fd);
	if (current_command && current_command->command)
	{
		finalize_command(&current_command, &root);
		if (!error_detected)
			execute_and_free_tree(root, shell, params.command_count, fd);
	}
	else if (current_command)
		free_command(current_command);
}
