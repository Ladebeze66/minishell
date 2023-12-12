/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:41:34 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/07 14:10:45 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*allocate_exit_status_str(void)
{
	char	*exit_status_str;

	exit_status_str = malloc(sizeof(char) * 12);
	if (exit_status_str == NULL)
	{
		perror("Erreur d'allocation mémoire $");
		return (NULL);
	}
	return (exit_status_str);
}

static int	num_to_str(int num, char *str, int base)
{
	int	i;
	int	rem;

	i = 0;
	if (num == 0)
	{
		str[i++] = '0';
	}
	else
	{
		while (num != 0)
		{
			rem = num % base;
			if (rem > 9)
				str[i++] = (rem - 10) + 'a';
			else
				str[i++] = rem + '0';
			num /= base;
		}
	}
	str[i] = '\0';
	return (i);
}

static void	int_to_str(int num, char *str, int base)
{
	int	isnegative;
	int	length;

	isnegative = 0;
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return ;
	}
	if (num < 0 && base == 10)
	{
		isnegative = 1;
		num = -num;
	}
	length = num_to_str(num, str, base);
	if (isnegative)
	{
		str[length] = '-';
		str[length + 1] = '\0';
		length++;
	}
	reverse_str(str, length);
}

static char	*get_exit_status_str(t_minishell *shell)
{
	char	*exit_status_str;

	exit_status_str = allocate_exit_status_str();
	if (exit_status_str == NULL)
		return (NULL);
	int_to_str(shell->last_exit_status, exit_status_str, 10);
	return (exit_status_str);
}

char	*get_variable_value(const char *variable_name, t_minishell *shell)
{
	const char	*name_to_search;
	char		*value;

	name_to_search = skip_dollar(variable_name);
	if (ft_strcmp(name_to_search, "?") == 0)
	{
		value = get_exit_status_str(shell);
		return (value);
	}
	value = search_env_variable(name_to_search, shell);
	return (value);
}
