NAME		:= 	minishell

DIR			:=	srcs/

DIRB		:=	srcs_bonus/

SRCS		:= 	main.c \
				errors.c \
				parsing/parse.c \
				parsing/parse_quote.c \
				parsing/get_env.c \
				commands/command_manager.c \
				commands/export.c \
				commands/env.c \
				commands/cd.c \
				commands/pwd.c \
				commands/exit.c \
				commands/ls.c \
				commands/mini_echo.c
			
OBJS		:=	$(patsubst %.c, $(DIR)%.o, $(SRCS))

CC			:= cc

FLAGS 		:= -Wall -Werror -Wextra -I includes -g

LIB			:= srcs/libs/libft/libft.a

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

all: ${NAME}

${NAME}: ${OBJS} ${LIB}
	@${CC} -o ${NAME} ${OBJS} ${LIB} -lreadline
	@printf "$(_BOLD)$(NAME)$(_RESET) compiled $(_GREEN)$(_BOLD)successfully$(_RESET)\n\n"

${LIB}:
	@printf "$(_BOLD)$(_UNDER)$(_YELLOW)                            LIBFT                           \n"
	@make --no-print-directory -C srcs/libs/libft

${DIR}%.o: ${DIR}%.c
	@${CC} ${FLAGS} -o $@ -c $<
	@$(eval CURR_OBJ=$(shell echo $$(( $(CURR_OBJ) + 1 ))))
	@$(eval PERCENT=$(shell echo $$(( $(CURR_OBJ) * 100 / $(OBJS_TOTAL) ))))
	@printf "$(_GREEN)($(_BOLD)%3s%%$(_RESET)$(_GREEN)) $(_RESET)Compiling $(_BOLD)$(_PURPLE)$<$(_RESET)\n" "$(PERCENT)"
	
clean:
	@rm -f ${OBJS}
	@make --no-print-directory -C srcs/libs/libft clean
	@printf "\n$(_BOLD)All objects are $(_GREEN)cleaned $(_RESET)! 🎉\n\n"

fclean: clean
	@rm -f ${NAME}
	@make --no-print-directory -C srcs/libs/libft clean fclean
	@printf "Cleaned $(_BOLD)$(NAME)$(_RESET) !\n\n"

re: fclean all

.PHONY: clean fclean re all
