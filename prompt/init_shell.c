/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:21:25 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 15:47:18 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_new_env_entry(char *name, char *value)
{
	char	*new_env_entry;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	if (value)
	{
		value_len = ft_strlen(value);
	}
	else
	{
		value_len = 0;
	}
	new_env_entry = malloc(name_len + value_len + 2);
	if (!new_env_entry)
		exit(EXIT_FAILURE);
	ft_strcpy(new_env_entry, name);
	ft_strcat(new_env_entry, "=");
	if (value)
		ft_strcat(new_env_entry, value);
	return (new_env_entry);
}

static char	*process_env_entry(char *env_entry)
{
	char	*name;
	char	*value;
	char	*new_env_entry;

	name = extract_name(env_entry);
	value = extract_value(env_entry);
	new_env_entry = create_new_env_entry(name, value);
	free(name);
	free(value);
	return (new_env_entry);
}

static void	init_environ(t_minishell *shell, char **envp)
{
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	shell->environ = malloc((count + 1) * sizeof(char *));
	if (!shell->environ)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		shell->environ[i] = process_env_entry(envp[i]);
		i++;
	}
	shell->environ[count] = NULL;
}

t_minishell	init_minishell(char **envp, char **builtin_str,
			int (**builtin_func)(char **, t_minishell *))
{
	t_minishell	shell;

	shell.builtin_str = builtin_str;
	shell.builtin_func = builtin_func;
	init_environ(&shell, envp);
	shell.last_exit_status = 0;
	shell.tokenizer = malloc(sizeof(t_Tokenizer));
	if (!shell.tokenizer)
		return (shell);
	shell.tokenizer->state = NORMAL;
	shell.tokenizer->tokens = NULL;
	shell.tokenizer->token = NULL;
	shell.tokenizer->token_length = 0;
	shell.tokenizer->input_pos = 0;
	shell.tokenizer->token_pos = 0;
	shell.tokenizer->in_quotes = false;
	shell.tokenizer->variable = 0;
	shell.tokenizer->symbol = true;
	shell.is_piped = false;
	return (shell);
}

bool	is_builtin_command(const char *command, t_minishell *shell)
{
	int		i;

	i = 0;
	while (shell->builtin_str[i] != NULL)
	{
		if (ft_strcmp(command, shell->builtin_str[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
