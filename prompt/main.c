/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:37:18 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 18:52:00 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**initialize_builtin_str(void)
{
	char	**local_builtin_str;

	local_builtin_str = malloc(8 * sizeof(char *));
	if (!local_builtin_str)
		return (NULL);
	local_builtin_str[0] = "cd";
	local_builtin_str[1] = "echo";
	local_builtin_str[2] = "exit";
	local_builtin_str[3] = "export";
	local_builtin_str[4] = "env";
	local_builtin_str[5] = "pwd";
	local_builtin_str[6] = "unset";
	local_builtin_str[7] = NULL;
	return (local_builtin_str);
}

t_builtin_func_t	*initialize_builtin_func(void)
{
	t_builtin_func_t	*local_builtin_func;

	local_builtin_func = malloc(8 * sizeof(int (*)(char **, t_minishell *)));
	if (!local_builtin_func)
		return (NULL);
	local_builtin_func[0] = &builtin_cd;
	local_builtin_func[1] = &builtin_echo_wrapper;
	local_builtin_func[2] = &builtin_exit;
	local_builtin_func[3] = &builtin_export;
	local_builtin_func[4] = &builtin_env;
	local_builtin_func[5] = &builtin_pwd;
	local_builtin_func[6] = &builtin_unset;
	local_builtin_func[7] = NULL;
	return (local_builtin_func);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		**local_builtin_str;
	int			(**local_builtin_func)(char **, t_minishell *);
	int			fd;

	(void)argc;
	(void)argv;
	fd = STDOUT_FILENO;
	local_builtin_str = initialize_builtin_str();
	local_builtin_func = initialize_builtin_func();
	if (!local_builtin_str || !local_builtin_func)
	{
		return (1);
	}
	rl_bind_key('\t', rl_complete);
	shell = init_minishell(envp, local_builtin_str, local_builtin_func);
	prompt_loop(&shell, fd);
	free(local_builtin_str);
	free(local_builtin_func);
	return (0);
}
