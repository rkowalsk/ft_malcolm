NAME = ft_malcolm

HEADERS_DIR = includes

LIBFT_DIR = libft

HEADERS =	$(HEADERS_DIR)/libft.h \
			$(HEADERS_DIR)/ft_malcolm.h

LIBFT_FILE = $(LIBFT_DIR)/libft.a

SRCS =	srcs/main.c \
		srcs/print_packet.c \
		srcs/parse_params.c \
		srcs/parse_mac.c

OBJS = ${SRCS:.c=.o}

COMPILER = gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT_FILE)
	$(COMPILER) $(OBJS) $(LIBFT_FILE) -o $(NAME)

$(OBJS): %.o: %.c $(HEADERS)
	$(COMPILER) -Wall -Wextra -Werror -I$(HEADERS_DIR) -c $< -o $@

$(LIBFT_FILE):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
