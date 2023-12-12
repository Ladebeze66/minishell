# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 16:09:37 by fgras-ca          #+#    #+#              #
#    Updated: 2023/12/09 17:20:03 by fgras-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RST				= \033[0m
GRAY			= \033[0;90m
RED				= \033[0;91m
GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m
ORANGE			= \033[38;5;214m
# Nom du binaire à produire
NAME = minishell
LIBFT = libft.a

# Liste des fichiers sources
SRCS =	prompt/history.c \
		prompt/prompt.c \
		prompt/main.c \
		utils/utils.c \
		builtins/builtins.c \
		extern/extern.c \
		extern/extern_utils.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/echo.c \
		builtins/unset.c \
		builtins/env.c \
		builtins/builtins_utils.c \
		signal/ctrl.c \
		tokenize/tokenize_symbol.c \
		tokenize/tokenize_utils.c \
		tokenize/tokenize.c \
		prompt/init_shell.c \
		parsing/parse_error.c \
		parsing/redirection_utils.c \
		parsing/variable_utils.c \
		parsing/parse_utils.c \
		parsing/herodoc.c \
		parsing/variable.c \
		command/command_array.c \
		command/command_utils.c \
		parsing/parse.c \
		command/command.c \
		tokenize/quotes.c \
		parsing/parse_redirections.c \
		parsing/redirection.c \
		parsing/pipe_utils.c \
		parsing/pipe.c \
		parsing/tree.c \
		builtins/export_env.c \

       # Ajoutez ici les autres fichiers .c

SRC_DIR_LIBFT = libft/

SRC_LIBFT = $(addprefix $(SRC_DIR_LIBFT), $(LIBFT))

# Liste des fichiers objets correspondants aux fichiers sources
OBJS = $(SRCS:.c=.o)

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror

# Règle par défaut
all: $(NAME)

# Règle pour créer le binaire
$(NAME): $(OBJS)
	@echo "$(RED)Loading Libft...$(RST)"
	@make -C libft
	@echo "$(GREEN)Libft...Done. $(RST)"
	@echo "$(RED)Compilation minishell... $(RST)"
	@$(CC) $(CFLAGS) $(OBJS) $(SRC_LIBFT) -o $(NAME) -lreadline -g
	@echo "$(GREEN)Compilation complete. $(ORANGE)Type "./minishell" for execute the program!!$(RST)"
	@echo "\n$(RED)# Ⓛⓐⓓⓔⓑⓔⓩⓔ ⓐⓝⓓ Ⓒⓥⓤ #$(RST)\n"

# Règle pour créer les fichiers objets à partir des fichiers sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets
clean:
	@echo "$(RED)Cleaning Libft... $(RST)"
	@make -C libft clean
	@echo "$(GREEN)Libft cleaned!! $(RST)"
	@echo "$(RED)Deleating files objects... $(RST)"
	rm -f $(OBJS)
	@echo "$(GREEN)files deleted!! $(RST)"
	@echo "\n$(RED)# Ⓛⓐⓓⓔⓑⓔⓩⓔ ⓐⓝⓓ Ⓒⓥⓤ #$(RST)\n"

# Règle pour nettoyer les fichiers objets et le binaire
fclean: clean
	@echo "$(RED)fclean Libft... $(RST)"
	@make -C libft fclean
	@echo "$(GREEN)Libft cleaned!! $(RST)"
	@echo "$(RED)Delete program name... $(RST)"
	rm -f $(NAME)
	@echo "$(GREEN)File program deleted!! $(RST)"
	@echo "\n$(RED)# Ⓛⓐⓓⓔⓑⓔⓩⓔ ⓐⓝⓓ Ⓒⓥⓤ #$(RST)\n"

# Règle pour recompiler le projet entièrement
re: fclean all

# Règle pour exécuter les tests
test: re
	./$(NAME)

# Empêcher make d'être confus avec un fichier nommé comme une règle
.PHONY: all clean fclean re test
