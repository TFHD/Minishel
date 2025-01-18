# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albernar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 15:14:39 by albernar          #+#    #+#              #
#    Updated: 2025/01/13 14:58:33 by sabartho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES
CC = cc
FLAGS = -Wall -Wextra -Werror -g	

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# FOLDERS
OBJ_DIR = .objs

# SOURCES
LIBFT_PATH = ./lib/libft/
GET_NEXT_LINE_PATH = ./lib/get_next_line/

SRCS = \
main.c \
mandatory/pipex.c \
mandatory/pipex_utils.c \
mandatory/process_utils.c \
mandatory/utils.c \

SRCS_BONUS = \
main_bonus.c \
mandatory/pipex.c \
mandatory/pipex_utils.c \
mandatory/process_utils.c \
mandatory/utils.c \
bonus/here_doc_bonus.c \
bonus/here_doc_utils_bonus.c \

# OBJECTS
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

# EXECUTABLES
LIBFT_LIB = $(addprefix $(LIBFT_PATH), libft.a)
GET_NEXT_LINE_LIB = $(addprefix $(GET_NEXT_LINE_PATH), libgnl.a)
NAME = pipex
NAME_BONUS = pipex_bonus

# RULES
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(GET_NEXT_LINE_LIB) $(OBJS)
	@echo "$(YELLOW)Creating $(NAME)...$(RESET)"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) $(GET_NEXT_LINE_LIB) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT_LIB) $(GET_NEXT_LINE_LIB) $(BONUS_OBJS)
	@echo "$(YELLOW)Creating $(NAME_BONUS)...$(RESET)"
	@$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBFT_LIB) $(GET_NEXT_LINE_LIB) -o $(NAME_BONUS)
	@echo "$(GREEN)$(NAME_BONUS) created successfully!$(RESET)"
	
$(OBJ_DIR)/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) -I./includes -o $@ -c $<

$(LIBFT_LIB):
	@echo "$(YELLOW)Compiling LIBFT...$(RESET)"
	@make -C $(LIBFT_PATH) -s
	@echo "$(GREEN)LIBFT created successfully!$(RESET)"

$(GET_NEXT_LINE_LIB):
	@echo "$(YELLOW)Compiling GNL...$(RESET)"
	@make -C $(GET_NEXT_LINE_PATH) -s
	@echo "$(GREEN)GNL created successfully!$(RESET)"
	
clean:
	@echo "$(RED)Cleaning LIBFT files...$(RESET)"
	@make clean -C $(LIBFT_PATH) -s
	@echo "$(RED)Cleaning GNL files...$(RESET)"
	@make clean -C $(GET_NEXT_LINE_PATH) -s
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	
fclean: clean
	@echo "$(RED)Cleaning LIBFT files...$(RESET)"
	@make fclean -C $(LIBFT_PATH) -s
	@echo "$(RED)Cleaning GNL files...$(RESET)"
	@make fclean -C $(GET_NEXT_LINE_PATH) -s
	@echo "$(RED)Cleaning executables...$(RESET)"
	@rm -f $(NAME) $(NAME_BONUS)
	
re: fclean all

.PHONY: all clean fclean bonus re
