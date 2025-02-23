CC =	cc
CFLAGS =	-Wall -Wextra -Werror -fPIC
RM =	rm -f
NAME =	libft.a
SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl_fd.c ft_putnbr.c ft_strmapi.c \
ft_striteri.c ft_printf.c get_next_line.c
BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
DEST =	$(SRC:.c=.o)
BONUS_DEST = $(BONUS_SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

$(NAME) : $(DEST)
	@ar rcs $(NAME) $(DEST)

clean :
	@$(RM) $(DEST) $(BONUS_DEST)

fclean : clean
	@$(RM) $(NAME)

re: fclean all

bonus: $(DEST) $(BONUS_DEST)
	ar rcs $(NAME) $(DEST) $(BONUS_DEST)

.PHONY : all clean fclean re bonus
