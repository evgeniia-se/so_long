# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esergeev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 18:46:47 by esergeev          #+#    #+#              #
#    Updated: 2025/05/19 17:20:15 by esergeev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SOURCES = main.c gaming.c parser.c utils.c work_window.c clean.c flood_fill.c check_map.c
OBJECTS = $(SOURCES:.c=.o)
LIBFT = ./libft/libft.a

CC = cc
GDBFLAGS = -g
CFLAGS = -Wall -Wextra -Werror -DBUFFER_SIZE=42 -I./include -I./libft \
-DEVENT_CONFIGURE_NOTIFY=22 -DMASK_CONFIGURE_NOTIFY='(1L << 19)' \
-Imlx_linux
LDFLAGS = -L./libft/ -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

gdb: CFLAGS += $(GDBFLAGS)
gdb: re
$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJECTS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re gdb
