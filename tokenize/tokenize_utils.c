/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:41:31 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 11:23:56 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	if (tokens != NULL)
	{
		i = 0;
		while (tokens[i] != NULL)
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}

void	add_token_to_list(t_Tokenizer *tk)
{
	char	*token_to_add;

	if (tk->token_length > 0)
	{
		tk->token[tk->token_length] = '\0';
		token_to_add = strdup(tk->token);
		if (token_to_add != NULL)
		{
			tk->tokens[tk->token_pos++] = token_to_add;
		}
		tk->token_length = 0;
		tk->within_single_quotes = false;
		tk->within_double_quotes = false;
	}
	if (tk->token != NULL)
	{
		free(tk->token);
	}
	tk->token = malloc(1000);
	if (tk->token != NULL)
	{
		ft_memset(tk->token, 0, 1000);
	}
}

void	process_char(char input_char, t_Tokenizer *tk)
{
	if (tk->state == NORMAL)
	{
		handle_normal_state(input_char, tk);
	}
	else if (tk->state == SINGLE_QUOTE)
	{
		handle_single_quote_state(input_char, tk);
	}
	else if (tk->state == DOUBLE_QUOTE)
	{
		handle_double_quote_state(input_char, tk);
	}
}

void	init_vars(t_Tokenizer *tk, char *input)
{
	tk->state = NORMAL;
	tk->tokens = malloc(MAX_ARGS * sizeof(char *));
	tk->token = malloc(ft_strlen(input) + 1);
	tk->token_length = 0;
	tk->input_pos = 0;
	tk->token_pos = 0;
	if (!(tk->tokens) || !(tk->token))
	{
		write(STDERR_FILENO, "Minishell: allocation error\n", 29);
		exit(EXIT_FAILURE);
	}
}
