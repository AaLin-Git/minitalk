CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

NAME = minitalk
CLIENT = client
SERVER = server

SRCS_CLIENT = src/client.c
SRCS_SERVER = src/server.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

LIBFT_DIR = libs/Libft
LIBFT = $(LIBFT_DIR)/libft.a

$(NAME):  $(CLIENT) $(SERVER)

all: $(NAME)

$(CLIENT): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(CLIENT)

$(SERVER): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(SERVER)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	@$(RM) $(CLIENT) $(SERVER)
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re