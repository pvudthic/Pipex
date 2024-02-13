NAME	=	pipex
CC		=	cc
LIBFT_DIR = libft
SRC_DIR	=	src
OBJ_DIR =	obj
CFLAGS	=	-Wall -Wextra -Werror -Isrc

VPATH	=	src

SRC		=	pipex.c \
			pipex_util.c \
			split_arg.c


LIBFT	= $(LIBFT_DIR)/libft.a

SRC_OBJ = $(SRC:%.c=obj/%.o)

$(NAME): $(LIBFT) $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) $(LIBFT) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SRC_OBJ): $(OBJ_DIR)/%.o: %.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean:
	rm -rf $(OBJ_DIR)/*

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
