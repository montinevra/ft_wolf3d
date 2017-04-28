NAME = wolf3d 
CC = gcc 
SRC = src/main.c src/loadmap.c src/wolf3d.c src/mlx_driver.c src/mlx_handlers.c src/draw.c
OBJ := $(SRC:.c=.o) 
CFLAGS = -Wall -Wextra -Werror 
LIBDIR = -L./libft -L./minilibx_macos
LIBS = -lft -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re alloc


all: $(NAME)


$(NAME): $(SRC) libft/libft.a minilibx_macos/libmlx.a
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIBDIR) $(LIBS)

libft/libft.a:
	make -C ./libft

minilibx_macos/libmlx.a:
	make -C ./minilibx_macos

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

lclean: fclean
	make fclean -C ./libft
	make clean -C ./minilibx_macos
	
re: fclean all

alloc:  $(SRC) libft/libft.a
	$(CC) -o $(NAME) $(SRC) alloc-wrap.c $(CFLAGS) $(LIBDIR) $(LIBS)

asan:  $(SRC) libft/libft.a
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIBDIR) $(LIBS) -fsanitize=address
