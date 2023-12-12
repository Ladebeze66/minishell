/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:25:07 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 13:55:02 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe_and_redirection(t_process_token_params *params, int fd)
{
	t_command_node	*new_node;

	if (is_pipe_token(params->tokens[*params->token_index], params->shell))
	{
		if (*params->current_command && (*params->current_command)->command)
		{
			new_node = create_command_node(*params->current_command);
			add_node_to_tree(params->root, new_node);
			*params->current_command = create_new_command();
			params->command_count++;
		}
	}
	else if (is_redirection_token(params->tokens[*params->token_index]))
	{
		if (*params->current_command && (*params->current_command)->command)
		{
			process_redirection
				(params, *params->current_command, params->shell, fd);
		}
	}
}

void	resolve_variable_and_add_to_command(t_process_token_params *params,
			char *token)
{
	char	*resolved_value;

	resolved_value = get_variable_value(token, params->shell);
	add_token_to_command_wrapper(params->current_command, resolved_value);
	free(resolved_value);
}

static void	handle_variable_token(t_process_token_params *params)
{
	char	*token;
	t_State	current_state;

	token = params->tokens[*params->token_index];
	current_state = params->shell->tokenizer->state;
	if (is_variable_resolvable(token, current_state))
	{
		resolve_variable_and_add_to_command(params, token);
	}
	else
	{
		add_token_to_command_wrapper(params->current_command, token);
	}
}

static void	handle_non_variable_token(t_process_token_params *params)
{
	add_token_to_command_wrapper(params->current_command,
		params->tokens[*params->token_index]);
}

void	handle_variable_and_other_tokens(t_process_token_params *params)
{
	char	*current_token;
	bool	variable;

	current_token = params->tokens[*params->token_index];
	variable = params->shell->tokenizer->variable;
	if (!variable && is_variable_token(current_token))
	{
		handle_variable_token(params);
	}
	else
	{
		handle_non_variable_token(params);
	}
}
