# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 16:50:54 by aapricot          #+#    #+#              #
#    Updated: 2020/08/07 20:11:18 by aapricot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC_DIR = ./
INC_DIR = ./includes/
SRC = $(addprefix ft_,\
	memset.c bzero.c memcpy.c memccpy.c memmove.c memchr.c memcmp.c strlen.c \
	strnlen.c strdup.c strcpy.c strncpy.c strcat.c strncat.c strlcat.c \
	strchr.c strrchr.c strstr.c strnstr.c strcmp.c strncmp.c atoi.c isalpha.c \
	isdigit.c isalnum.c isascii.c isprint.c toupper.c tolower.c \
	memalloc.c memdel.c strnew.c strdel.c strclr.c striter.c striteri.c strmap.c \
	strmapi.c strequ.c strnequ.c strsub.c strjoin.c strtrim.c strsplit.c itoa.c \
	putchar.c putstr.c putendl.c putnbr.c putchar_fd.c putstr_fd.c putendl_fd.c \
	putnbr_fd.c isspace.c matfree.c lstnew.c lstdelone.c lstdel.c lstadd.c \
	lstiter.c lstmap.c wc.c swap.c absolute.c swap_double.c isupper.c \
	isbase.c strtol.c swap_int.c) get_next_line.c
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
OBJ = $(SRC:.c=.o) 

.PHONY: all
all : $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@echo 'libft.a created'

$(OBJ): %.o: %.c $(INC_DIR)libft.h
	@$(CC) $(CFLAGS) -c $*.c -I $(INC_DIR)

.PHONY: clean
clean:
	@echo 'deleting object files'
	@rm -rf $(OBJ)

.PHONY: fclean
fclean: clean
	@echo 'deleting libft.a'
	@rm -f $(NAME)

.PHONY: re
re: fclean all