NAME	= 	libft.a
SRCS	= 	ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memset.c \
			ft_memcmp.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strnstr.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_calloc.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

OBJS		:=	$(patsubst %.c, %.o, $(SRCS))

HEAD 	=	libft.h

AR 		= 	ar -rcs

CC		=	cc

FLAGS 	= 	-Wall -Werror -Wextra

TPUT 		:= tput -T xterm-256color
_BOLD 		:= $(shell $(TPUT) bold)
_GREEN 		:= $(shell $(TPUT) setaf 2)
_RESET 		:= $(shell $(TPUT) sgr0)
_PURPLE 	:= $(shell $(TPUT) setaf 5)
_YELLOW 	:= $(shell $(TPUT) setaf 3)

OBJS_TOTAL	= $(words $(OBJS))
N_OBJS		:= $(shell find $(DIR) -type f -name $(OBJS) 2>/dev/null | wc -l)
OBJS_TOTAL	:= $(shell echo $$(( $(OBJS_TOTAL) - $(N_OBJS) )))
CURR_OBJ	= 0

all: ${NAME}

$(NAME): ${OBJS}
	@${AR} ${NAME} ${OBJS}
	@printf "$(_BOLD)$(NAME)$(_RESET) compiled $(_GREEN)$(_BOLD)successfully$(_RESET)\n"
	
%.o: %.c
	@${CC} ${FLAGS} -o $@ -c $<
	@$(eval CURR_OBJ=$(shell echo $$(( $(CURR_OBJ) + 1 ))))
	@$(eval PERCENT=$(shell echo $$(( $(CURR_OBJ) * 100 / $(OBJS_TOTAL) ))))
	@printf "$(_YELLOW)LIBFT :$(_RESET) $(_GREEN)($(_BOLD)%3s%%$(_RESET)$(_GREEN)) $(_RESET)Compiling $(_BOLD)$(_PURPLE)$<$(_RESET)\n" "$(PERCENT)"

clean:
	@rm -f ${OBJS}
	@printf "Cleaned $(_BOLD)$(OBJS)$(_RESET)\n"

fclean: clean
	@rm -f ${NAME}
	@printf "Cleaned $(_BOLD)$(NAME)$(_RESET)\n"

re: fclean all

.PHONY: clean fclean re all
