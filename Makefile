NAME = wolf3d 
CC = gcc 
SRCDIR = src
SRC = main.c loadmap.c wolf3d.c draw.c \
	mlx_driver.c mlx_handlers.c mlx_key_handlers.c mlx_mouse_handlers.c \
	more_math.c
SRC := $(SRC:%.c=$(SRCDIR)/%.c)
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
	make clean -C ./libft
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
