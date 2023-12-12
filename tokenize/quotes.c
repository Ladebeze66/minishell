/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:40:11 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 16:19:24 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	are_only_quotes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (ft_strcmp(tokens[i], "\"\"") != 0
			&& ft_strcmp(tokens[i], "''") != 0)
			return (0);
		i++;
	}
	return (1);
}

void	handle_normal_state(char input_char, t_Tokenizer *tk)
{
	if (input_char == '\'')
	{
		tk->state = SINGLE_QUOTE;
	}
	else if (input_char == '\"')
	{
		tk->state = DOUBLE_QUOTE;
	}
	else
	{
		tk->token[(tk->token_length)++] = input_char;
		tk->symbol = true;
	}
}

void	handle_double_quote_state(char input_char, t_Tokenizer *tk)
{
	if (input_char != '\"')
	{
		tk->token[(tk->token_length)++] = input_char;
		if (input_char == '$')
		{
			tk->variable = 0;
		}
		if (is_simple_symbol(input_char) == true)
			tk->symbol = false;
	}
	else
	{
		if (tk->token_length > 0 && tk->token[tk->token_length - 1] == ' ')
		{
			tk->token[(tk->token_length)++] = input_char;
		}
		else
		{
			tk->state = NORMAL;
			tk->symbol = true;
		}
	}
}

void	handle_single_quote_state(char input_char, t_Tokenizer *tk)
{
	if (input_char != '\'')
	{
		tk->token[(tk->token_length)++] = input_char;
		if (input_char == '$')
		{
			tk->variable = 1;
		}
		if (is_simple_symbol(input_char) == true)
		{
			tk->symbol = false;
		}
	}
	else
	{
		if (tk->token_length > 0 && tk->token[tk->token_length - 1] == ' ')
		{
			tk->token[(tk->token_length)++] = input_char;
		}
		else
		{
			tk->state = NORMAL;
		}
	}
}

char	**handle_unclosed_quotes(char ***tokens, int token_pos)
{
	int	i;

	i = 0;
	if (tokens == NULL || *tokens == NULL)
	{
		return (NULL);
	}
	write(2, RED"Error: quote not closed\n"RST, 32);
	if (token_pos > 0)
	{
		while (i < token_pos)
		{
			free((*tokens)[i]);
			i++;
		}
		free(*tokens);
	}
	*tokens = NULL;
	return (NULL);
}
