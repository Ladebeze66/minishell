/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:14:12 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 15:55:33 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_history_entry(HIST_ENTRY **the_history_list, int i)
{
	printf("%d: %s\n", i + history_base, the_history_list[i]->line);
}

void	display_history_list(void)
{
	int			i;
	HIST_ENTRY	**the_history_list;

	i = 0;
	the_history_list = history_list();
	if (the_history_list)
	{
		while (the_history_list[i])
		{
			display_history_entry(the_history_list, i);
			i++;
		}
	}
}

void	search_in_history(HIST_ENTRY **the_history_list
		, const char *search_string)
{
	int	i;

	i = 0;
	while (the_history_list[i])
	{
		if (ft_strstr(the_history_list[i]->line, search_string))
		{
			printf("%d: %s\n", i + history_base, the_history_list[i]->line);
		}
		i++;
	}
}

void	search_history(void)
{
	char		*search_string;
	HIST_ENTRY	**the_history_list;

	search_string = readline("Rechercher dans l'historique: ");
	if (search_string && *search_string)
	{
		the_history_list = history_list();
		if (the_history_list)
		{
			search_in_history(the_history_list, search_string);
		}
	}
	if (search_string)
	{
		free(search_string);
	}
}
