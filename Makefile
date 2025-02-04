NAME		:= 	minishell
NAME_BONUS	:= 	minishell_bonus

OBJS_DIR	:= .objs/

DIR			:=	srcs/

DIRB		:=	srcs_bonus/

SRCS		:= 	leak_protector/leak_protector.c \
				leak_protector/leak_protector_list.c \
				leak_protector/func/lp_strdup.c \
				leak_protector/func/lp_strsjoin.c \
				leak_protector/func/lp_substr.c \
				parsing/ast/ast_tree.c \
				parsing/ast/ast_utils.c \
				parsing/ast/command_builder.c \
				parsing/ast/redirection_list.c \
				parsing/token/token_args.c \
				parsing/token/token_error.c \
				parsing/token/token_list.c \
				parsing/token/token_parser_utils.c \
				parsing/token/token_parser.c \
				parsing/quotes/parsing_quote.c \
				parsing/expand/expand.c \
				parsing/expand/expand_utils.c \
				shell/env/create_env.c \
				shell/env/env_list.c \
				shell/env/env_utils.c \
				shell/prompt/prompt_builder.c \
				shell/prompt/prompt.c \
				shell/exec/exec_core.c \
				shell/exec/exec.c \
				shell/exec/exec_utils.c \
				shell/exec/exec_utils2.c \
				shell/builtins/builtins.c \
				shell/builtins/cmd/pwd.c \
				shell/builtins/cmd/cd.c \
				shell/builtins/cmd/echo.c \
				shell/builtins/cmd/export.c \
				shell/builtins/cmd/export_utils.c \
				shell/builtins/cmd/unset.c \
				shell/builtins/cmd/exit.c \
				shell/builtins/cmd/env.c \
				shell/exec/redirection/heredoc.c \
				shell/exec/redirection/in_out_append.c \
				shell/exec/redirection/redirect_utils.c \
				shell/exec/redirection/redirection.c \
				signal.c \
				main.c \

SRCS_BONUS	:=	parsing/expand/wildcards/wildcards_pattern_bonus.c \
				parsing/expand/wildcards/wildcards_segments_bonus.c \
				parsing/expand/wildcards/wildcards_utils_bonus.c \
				parsing/expand/wildcards/wildcards_utils2_bonus.c \
				parsing/expand/wildcards/wildcards_bonus.c \
			
OBJS		:=	$(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))
OBJS_BONUS	:=	$(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS_BONUS))

CC			:= cc

FLAGS		:= -Wall -Werror -Wextra -Iincludes/ast -Iincludes/debug -Iincludes/parsing -Iincludes/shell -Iincludes -g

LIB			:= libft/libft.a

TPUT 					= tput -T xterm-256color
_RESET 					:= $(shell $(TPUT) sgr0)
_BOLD 					:= $(shell $(TPUT) bold)
_ITALIC 				:= $(shell $(TPUT) sitm)
_UNDER 					:= $(shell $(TPUT) smul)
_GREEN 					:= $(shell $(TPUT) setaf 2)
_YELLOW 				:= $(shell $(TPUT) setaf 3)
_RED 					:= $(shell $(TPUT) setaf 1)
_GRAY 					:= $(shell $(TPUT) setaf 8)
_PURPLE 				:= $(shell $(TPUT) setaf 5)

OBJS_TOTAL	= $(words $(OBJS))
N_OBJS		:= $(shell find $(DIR) -type f -name $(OBJS) 2>/dev/null | wc -l)
OBJS_TOTAL	:= $(shell echo $$(( $(OBJS_TOTAL) - $(N_OBJS) )))
CURR_OBJ	= 0

all: $(OBJS_DIR) $(NAME)

bonus: $(OBJS_DIR) $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) $(LIB)
	@mkdir -p .objs/parsing/expand/wildcards
	@$(CC) $(FLAGS) -o .objs/parsing/expand/wildcards/wildcards_pattern_bonus.o -c ./srcs/parsing/expand/wildcards/wildcards_pattern_bonus.c
	@$(CC) $(FLAGS) -o .objs/parsing/expand/wildcards/wildcards_segments_bonus.o -c ./srcs/parsing/expand/wildcards/wildcards_segments_bonus.c
	@$(CC) $(FLAGS) -o .objs/parsing/expand/wildcards/wildcards_utils_bonus.o -c ./srcs/parsing/expand/wildcards/wildcards_utils_bonus.c
	@$(CC) $(FLAGS) -o .objs/parsing/expand/wildcards/wildcards_utils2_bonus.o -c ./srcs/parsing/expand/wildcards/wildcards_utils2_bonus.c
	@$(CC) $(FLAGS) -o .objs/parsing/expand/wildcards/wildcards_bonus.o -c ./srcs/parsing/expand/wildcards/wildcards_bonus.c
	@${CC} ${FLAGS} -D BONUS=1 -o .objs/parsing/expand/expand.o -c ./srcs/parsing/expand/expand.c
	@${CC} ${FLAGS} -D BONUS=1 -o .objs/shell/exec/exec_core.o -c ./srcs/shell/exec/exec_core.c
	@${CC} -o ${NAME_BONUS} ${OBJS} $(OBJS_BONUS) ${LIB} -lreadline -D BONUS=1
	@printf "$(_BOLD)$(NAME_BONUS)$(_RESET) compiled $(_GREEN)$(_BOLD)successfully$(_RESET)\n\n"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(addprefix $(OBJS_DIR), $(dir $(SRCS)))

${NAME}: ${OBJS} ${LIB}
	@${CC} ${FLAGS} -o .objs/parsing/expand/expand.o -c ./srcs/parsing/expand/expand.c
	@${CC} ${FLAGS} -o .objs/shell/exec/exec_core.o -c ./srcs/shell/exec/exec_core.c
	@${CC} -o ${NAME} ${OBJS} ${LIB} -lreadline
	@printf "$(_BOLD)$(NAME)$(_RESET) compiled $(_GREEN)$(_BOLD)successfully$(_RESET)\n\n"

${LIB}:
	@printf "$(_BOLD)$(_UNDER)$(_YELLOW)                            LIBFT                           $(_RESET)\n"
	@make --no-print-directory -C libft

${OBJS_DIR}%.o: ${DIR}%.c
	@${CC} ${FLAGS} -o $@ -c $<
	@$(eval CURR_OBJ=$(shell echo $$(( $(CURR_OBJ) + 1 ))))
	@$(eval PERCENT=$(shell echo $$(( $(CURR_OBJ) * 100 / $(OBJS_TOTAL) ))))
	@printf "$(_GREEN)($(_BOLD)%3s%%$(_RESET)$(_GREEN)) $(_RESET)Compiling $(_BOLD)$(_PURPLE)$<$(_RESET)\n" "$(PERCENT)"

clean:
	@rm -rf ${OBJS_DIR}
	@make --no-print-directory -C libft clean
	@printf "\n$(_BOLD)All objects are $(_GREEN)cleaned $(_RESET)! 🎉\n\n"

fclean: clean
	@rm -f ${NAME}
	@rm -f ${NAME_BONUS}
	@make --no-print-directory -C libft clean fclean
	@printf "Cleaned $(_BOLD)$(NAME)$(_RESET) !\n\n"

re: fclean all

.PHONY: bonus clean fclean re all
