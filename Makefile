NAME	=	pipex
CC		=	cc
LIBFT_DIR = libft
SRC_DIR	=	src
CFLAGS	=	-Wall -Werror -Wextra

SRC		=	pipex.c \
			check_input.c \
			error_msg.c \
			initialize.c \
			initialize_helper.c \
			main.c


LIBFT	= $(LIBFT_DIR)/libft.a

SRC_OBJ = $(SRC:%.c=%.o)

$(NAME): $(LIBFT) $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) $(LIBFT) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SRC_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean:
	rm -rf $(SRC_OBJ)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
