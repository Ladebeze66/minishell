/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:09:39 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 01:03:54 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_quotes(char current_char, t_Tokenizer *tk)
{
	if ((tk->state == NORMAL && (current_char == '\'' || current_char == '\"'))
		|| (tk->state == SINGLE_QUOTE && current_char == '\'')
		|| (tk->state == DOUBLE_QUOTE && current_char == '\"'))
	{
		if (tk->state == NORMAL)
		{
			if (current_char == '\'')
			{
				tk->state = SINGLE_QUOTE;
			}
			else
			{
				tk->state = DOUBLE_QUOTE;
			}
		}
		else
			tk->state = NORMAL;
		tk->input_pos++;
		return (true);
	}
	return (false);
}

void	process_remaining_chars(char current_char, char *input, t_Tokenizer *tk)
{
	if (tk->state != NORMAL)
	{
		process_char(current_char, tk);
		tk->input_pos++;
		return ;
	}
	if (current_char == ' ' || current_char == '\t')
	{
		if (tk->token_length > 0)
		{
			add_token_to_list(tk);
		}
		handle_spaces_and_tabs(input, tk);
	}
	else if (is_special_symbol(current_char, input[tk->input_pos + 1]))
		add_special_symbol(input, tk);
	else
	{
		process_char(current_char, tk);
		tk->variable = 0;
		tk->input_pos++;
	}
}

void	process_input_char(char *input, t_Tokenizer *tk)
{
	char	current_char;

	current_char = input[tk->input_pos];
	if (!handle_quotes(current_char, tk))
	{
		process_remaining_chars(current_char, input, tk);
	}
}

void	tokenize_loop(char *input, t_Tokenizer *tk)
{
	while (input[tk->input_pos] != '\0')
	{
		process_input_char(input, tk);
	}
	if (tk->token_length > 0)
	{
		add_token_to_list(tk);
	}
}

char	**tokenize_and_parse_input(char *input, t_minishell *shell, int fd)
{
	char	**result;

	if (is_only_spaces(input))
		return (NULL);
	init_vars(shell->tokenizer, input);
	tokenize_loop(input, shell->tokenizer);
	if (shell->tokenizer->state == SINGLE_QUOTE
		|| shell->tokenizer->state == DOUBLE_QUOTE)
	{
		result = handle_unclosed_quotes(&shell->tokenizer->tokens,
				shell->tokenizer->token_pos);
		free(shell->tokenizer->token);
		return (result);
	}
	add_token_to_list(shell->tokenizer);
	if (shell->tokenizer->tokens != NULL)
		shell->tokenizer->tokens[shell->tokenizer->token_pos] = NULL;
	parse_tokens(shell->tokenizer->tokens, shell, fd);
	free(shell->tokenizer->token);
	free_tokens(shell->tokenizer->tokens);
	return (NULL);
}
