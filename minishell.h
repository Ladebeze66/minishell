/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:11:33 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/12/10 14:08:16 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>

# define RST "\033[0m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define ORANGE "\033[38;5;214m"

# define MAX_ARGS 10000
# define DELIM " \t\r\n\a"
# define CONTINUE_SHELL 0
# define EXIT_SHELL 1

typedef enum s_redirection_mode
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	REDIRECT_UNKNOWN
}	t_redirection_mode;

typedef enum s_state
{
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_State;

typedef struct s_tokenizer
{
	t_State	state;
	char	**tokens;
	char	*token;
	int		token_length;
	int		input_pos;
	int		token_pos;
	bool	in_quotes;
	bool	within_single_quotes;
	bool	within_double_quotes;
	bool	variable;
	bool	symbol;
}	t_Tokenizer;

typedef struct s_minishell
{
	char		**builtin_str;
	char		**environ;
	int			(**builtin_func)(char **, struct s_minishell *);
	int			last_exit_status;
	t_Tokenizer	*tokenizer;
	bool		is_piped;
	int			exit_status;
}	t_minishell;

typedef struct s_command
{
	char	*command;
	char	**args;
	int		arg_count;
}	t_command;

typedef struct s_redirection
{
	int	stdin_backup;
	int	stdout_backup;
}	t_redirection;

typedef struct s_pipe_struct
{
	int	fds[2];
}	t_pipe_struct;

typedef struct s_command_node
{
	t_command				*command;
	struct s_command_node	*left;
	struct s_command_node	*right;
}	t_command_node;

typedef struct s_process_token_params
{
	char			**tokens;
	int				*token_index;
	t_command		**current_command;
	t_command_node	**root;
	t_minishell		*shell;
	int				command_count;
}	t_process_token_params;

typedef struct s_child_process_params
{
	int			i;
	int			*pipe_fds;
	int			command_count;
	int			fd;
	t_command	**commands;
	t_minishell	*shell;
}	t_child_process_params;

typedef struct s_process_params
{
	int			*pipe_fds;
	t_command	**commands;
	t_minishell	*shell;
	int			command_count;
	int			fd;
}	t_process_params;

typedef int	(*t_builtin_func_t)(char **, t_minishell *);

//prompt
void				prompt_loop(t_minishell *shell, int fd);
t_minishell			init_minishell(char **envp, char **builtin_str,
						int (**builtin_func)(char **, t_minishell *));
//history
void				display_history_entry(HIST_ENTRY **the_history_list, int i);
void				display_history_list(void);
void				search_in_history(HIST_ENTRY **the_history_list,
						const char *search_string);
void				search_history(void);
//builtins
int					builtin_echo_wrapper(char **args, t_minishell *shell);
int					builtin_cd(char **args, t_minishell *shell);
int					builtin_echo(char **args, t_minishell *shell, int fd);
int					builtin_exit(char **args, t_minishell *shell);
int					builtin_env(char **args, t_minishell *shell);
int					builtin_pwd(char **args, t_minishell *shell);
int					builtin_export(char **args, t_minishell *shell);
int					num_builtins(t_minishell *shell);
int					execute_builtin(char **args, t_minishell *shell);
int					builtin_unset(char **args, t_minishell *shell);
int					export_set_env(char **args, t_minishell *shell);
int					count_env_vars(char **environ);
char				**copy_env(char **environ, int env_size);
void				sort_env(char **env, int env_size);
int					add_new_env_entry(t_minishell *shell, char *new_env_entry);
int					replace_env_entry(t_minishell *shell, char *new_env_entry);
char				*extract_name(char *env_entry);
char				*extract_value(char *env_entry);
t_builtin_func_t	*initialize_builtin_func(void);
//Exécutions
pid_t				create_process(char *path, char **args, char **environ);
pid_t				execute_external_command(char **args, char **environ);
char				*find_executable(const char *cmd, char **environ);
//tokenize
char				**tokenize_and_parse_input(char *input,
						t_minishell *shell, int fd);
void				tokenize_loop(char *input, t_Tokenizer *tk);
void				init_vars(t_Tokenizer *tk, char *input);
void				process_char(char input_char, t_Tokenizer *tk);
void				add_token_to_list(t_Tokenizer *tk);
void				free_tokens(char **tokens);
void				add_special_symbol(char *input, t_Tokenizer *tk);
void				handle_spaces_and_tabs(char *input, t_Tokenizer *tk);
void				handle_empty_quotes(char *input, t_Tokenizer *tk);
bool				is_special_symbol(char c, char next_c);
bool				is_simple_symbol(char c);
void				process_input_char(char *input, t_Tokenizer *tk);
void				handle_other_chars(char *input, t_Tokenizer *tk);
void				handle_special_symbol(char *input, t_Tokenizer *tk);
void				handle_spaces_or_tabs(char *input, t_Tokenizer *tk);
bool				is_space_or_tab(char current_char);
void				handle_quote_transition(char *input, t_Tokenizer *tk);
bool				is_quote_transition(char current_char, t_Tokenizer *tk);
char				*replace_env_vars_in_string(const char *str,
						t_minishell *shell);
//quotes
void				handle_normal_state(char input_char, t_Tokenizer *tk);
void				handle_single_quote_state(char input_char, t_Tokenizer *tk);
void				handle_double_quote_state(char input_char, t_Tokenizer *tk);
char				**handle_unclosed_quotes(char ***tokens, int token_pos);
int					are_only_quotes(char **tokens);
//var $
char				*get_variable_value(const char *variable_name,
						t_minishell *shell);
const char			*skip_dollar(const char *variable_name);
void				reverse_str(char *str, int length);
char				*search_env_variable(const char *name_to_search,
						t_minishell *shell);
//utils
char				*get_env_value(const char *key, char **environ);
int					is_only_spaces(const char *str);
//gestions signaux ctrl-c ctrl-D ctrl-
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				setup_signal_handlers(void);
//parsing
void				parse_tokens(char **tokens, t_minishell *shell, int fd);
bool				is_pipe_token(char *token, t_minishell *shell);
bool				is_redirection_token(char *token);
bool				is_variable_token(char *token);
void				add_token_to_command_wrapper(t_command **command,
						char *token);
int					is_variable_resolvable(char *token, t_State current_state);
void				handle_variable_and_other_tokens(
						t_process_token_params *params);
void				handle_pipe_and_redirection(t_process_token_params *params,
						int fd);
void				execute_and_free_tree(t_command_node *root,
						t_minishell *shell, int command_count, int fd);
int					check_syntax_error(char **tokens, int token_index,
						bool in_quotes, t_minishell *shell);
//redirections
void				process_redirection(t_process_token_params *params,
						t_command *commands, t_minishell *shell, int fd);
void				save_standard_descriptors(t_redirection *redir);
void				restore_standard_descriptors(t_redirection *redir);
void				heredoc_input(const char *delimiter);
void				configure_redirection(char *file, int mode);
//pipes
void				process_pipe(t_command **command, t_minishell *shell,
						int command_count, int fd);
void				heredoc_input(const char *delimiter);
void				close_all_pipes(int *pipe_fds, int count);
void				setup_child_process(t_child_process_params *params);
//command
void				reset_command(t_command *command);
void				free_command(t_command *command);
void				add_token_to_command(t_command *command, char *token);
void				execute_command(t_command *command,
						t_minishell *shell, int fd);
bool				is_builtin_command(const char *command, t_minishell *shell);
t_command			*create_new_command(void);
char				**build_args_array(t_command *command);
void				free_args_array(char **args);
int					execute_builtin_and_free(char **args,
						t_minishell *shell, int fd);
//tree
t_command_node		*create_command_node(t_command *command);
void				add_node_to_tree(t_command_node **root,
						t_command_node *new_node);
void				execute_command_tree(t_command_node *node,
						t_minishell *shell, int command_count, int fd);
void				free_command_tree(t_command_node *node);

#endif
