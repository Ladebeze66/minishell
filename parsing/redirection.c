/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:42:58 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 13:56:12 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	configure_redirection(char *file, int mode)
{
	int	fd;

	if (mode == REDIRECT_IN)
	{
		fd = open(file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (mode == REDIRECT_OUT)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (mode == REDIRECT_APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (mode == REDIRECT_HEREDOC)
	{
		heredoc_input(file);
	}
}

static t_redirection_mode	get_redirection_mode(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	if (ft_strcmp(token, ">>") == 0)
		return (REDIRECT_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (REDIRECT_HEREDOC);
	perror(RED"Redirection non reconnue"RST);
	return (REDIRECT_UNKNOWN);
}

static void	handle_redirection(char *token, t_redirection_mode redirection_mode)
{
	if (redirection_mode == REDIRECT_HEREDOC)
		heredoc_input(token);
	else
		configure_redirection(token, redirection_mode);
}

void	process_redirection(t_process_token_params *params, t_command *commands,
			t_minishell*shell, int fd)
{
	t_redirection		redir;
	t_redirection_mode	redirection_mode;

	save_standard_descriptors(&redir);
	redirection_mode
		= get_redirection_mode(params->tokens[*(params->token_index)]);
	if (redirection_mode == REDIRECT_UNKNOWN)
		return ;
	(*(params->token_index))++;
	handle_redirection
		(params->tokens[*(params->token_index)], redirection_mode);
	execute_command(commands, shell, fd);
	restore_standard_descriptors(&redir);
	reset_command(*params->current_command);
}
