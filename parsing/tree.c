/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:03:54 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 13:56:39 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command_node	*create_command_node(t_command *command)
{
	t_command_node	*node;

	node = malloc(sizeof(t_command_node));
	if (node == NULL)
	{
		return (NULL);
	}
	node->command = command;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	add_node_to_tree(t_command_node **root, t_command_node *new_node)
{
	t_command_node	*current;

	if (*root == NULL)
	{
		*root = new_node;
	}
	else
	{
		current = *root;
		while (current->right != NULL)
		{
			current = current->right;
		}
		current->right = new_node;
	}
}

void	execute_command_tree(t_command_node *node, t_minishell *shell,
			int command_count, int fd)
{
	t_command		**commands_array;
	t_command_node	*current_node;
	int				i;

	i = 0;
	current_node = node;
	commands_array = malloc(sizeof(t_command *) * command_count);
	while (current_node != NULL && i < command_count)
	{
		commands_array[i] = current_node->command;
		current_node = current_node->right;
		i++;
	}
	process_pipe(commands_array, shell, command_count, fd);
	free(commands_array);
}

void	free_command_tree(t_command_node *node)
{
	if (node == NULL)
	{
		return ;
	}
	free_command_tree(node->left);
	free_command_tree(node->right);
	if (node->command)
	{
		free(node->command);
	}
	free(node);
}
