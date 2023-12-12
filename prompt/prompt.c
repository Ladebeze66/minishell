/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:51:21 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/09 18:49:47 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	disable_tab_completion(void)
{
	rl_bind_key('\t', rl_insert);
}

static void	process_input_line(t_minishell *shell, char *line, int fd)
{
	if (ft_strcmp(line, "history") == 0)
	{
		display_history_list();
	}
	else
	{
		tokenize_and_parse_input(line, shell, fd);
	}
}

void	prompt_loop(t_minishell *shell, int fd)
{
	char	*line;
	int		status;

	setup_signal_handlers();
	status = 1;
	using_history();
	disable_tab_completion();
	while (status)
	{
		line = readline("\001"ORANGE"\002Minishell$> \001"RST"\002");
		if (!line)
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (!is_only_spaces(line) && ft_strcmp(line, "") != 0)
		{
			add_history(line);
			process_input_line(shell, line, fd);
		}
		free(line);
	}
	clear_history();
}
