/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_symbol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:34:50 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 16:19:24 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_spaces_and_tabs(char *input, t_Tokenizer *tk)
{
	while (input[tk->input_pos] == ' ' || input[tk->input_pos] == '\t')
	{
		tk->input_pos++;
	}
}

void	add_special_symbol(char *input, t_Tokenizer *tk)
{
	if (tk->token_length > 0)
	{
		add_token_to_list(tk);
	}
	tk->token[0] = input[tk->input_pos++];
	tk->token_length = 1;
	if ((tk->token[0] == '>' && input[tk->input_pos] == '>')
		|| (tk->token[0] == '<' && input[tk->input_pos] == '<'))
	{
		tk->token[tk->token_length++] = input[tk->input_pos++];
	}
	tk->token[tk->token_length] = '\0';
	add_token_to_list(tk);
}

void	handle_empty_quotes(char *input, t_Tokenizer *tk)
{
	char	quote_type;
	int		start_pos;
	int		i;

	quote_type = input[tk->input_pos];
	start_pos = tk->input_pos;
	tk->input_pos++;
	while (input[tk->input_pos] != quote_type && input[tk->input_pos] != '\0')
	{
		tk->input_pos++;
	}
	if (input[tk->input_pos] == quote_type)
	{
		if (tk->input_pos - start_pos > 1)
		{
			i = start_pos + 1;
			while (i < tk->input_pos)
			{
				tk->token[tk->token_length++] = input[i];
				i++;
			}
			add_token_to_list(tk);
		}
		tk->input_pos++;
	}
}

bool	is_special_symbol(char c, char next_c)
{
	if (c == '|' || c == '<' || c == '>')
	{
		return (true);
	}
	if ((c == '>' && next_c == '>') || (c == '<' && next_c == '<'))
	{
		return (true);
	}
	return (false);
}

bool	is_simple_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
	{
		return (true);
	}
	return (false);
}
