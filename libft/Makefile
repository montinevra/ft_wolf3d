# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/25 20:54:37 by pvan-erp          #+#    #+#              #
#    Updated: 2017/03/09 17:15:19 by pvan-erp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = \
	ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strlen.c ft_strdup.c ft_strcpy.c \
	ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
	ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
	ft_strcmp.c ft_strncmp.c \
	ft_atoi.c ft_atoi_base.c ft_basetoi.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
	ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	ft_lstiter.c ft_lstmap.c ft_lstlen.c \
	ft_islower.c ft_isupper.c ft_isnumber.c ft_isblank.c ft_isspace.c \
	ft_strndup.c \
	ft_strresize.c ft_wrdlen.c ft_sqrt_ceil.c \
	ft_wcslen.c ft_ustrlen.c ft_itoa_base.c ft_itobase.c\
	get_next_line.c \
	ft_arrnew.c ft_arrlen.c ft_arrdel.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re test
	

all: $(NAME)
	

$(NAME): $(SRC)
	$(CC) -c $(SRC) $(CFLAGS)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


test: all
	$(CC) main.c alloc-wrap.c -L./ -lft
	./a.out
