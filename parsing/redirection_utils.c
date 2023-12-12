/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:33:34 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 13:29:36 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_standard_descriptors(t_redirection *redir)
{
	redir->stdin_backup = dup(STDIN_FILENO);
	redir->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_standard_descriptors(t_redirection *redir)
{
	if (redir->stdin_backup != -1)
	{
		dup2(redir->stdin_backup, STDIN_FILENO);
		close(redir->stdin_backup);
	}
	if (redir->stdout_backup != -1)
	{
		dup2(redir->stdout_backup, STDOUT_FILENO);
		close(redir->stdout_backup);
	}
}
