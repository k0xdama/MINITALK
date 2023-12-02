# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 19:28:28 by pmateo            #+#    #+#              #
#    Updated: 2023/12/02 20:44:45 by pmateo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

NAMECLIENT = client
NAMESERVER = server

SRC_CLIENT = SRCS/client.c 
SRC_SERVER = SRCS/server.c 
SRCBONUS_CLIENT = SRCS/client_bonus.c
SRCBONUS_SERVER = SRCS/server_bonus.c

OBJ_CLIENT = ${SRC_CLIENT:.c=.o}
OBJ_SERVER = ${SRC_SERVER:.c=.o}
OBJBONUS_CLIENT = ${SRCBONUS_CLIENT:.c=.o}
OBJBONUS_SERVER = ${SRCBONUS_SERVER:.c=.o}

INCLUDE = INCLUDES/minitalk.h
INCLUDE_BONUS = INCLUDES/minitalk_bonus.h

DIRLIBFT = ./LIBFT
LIBFT = ${DIRLIBFT}/libft.a
DIRPRINTF = ./PRINTF
PRINTF = ${DIRPRINTF}/libftprintf.a

${LIBFT}:
	make -s -C ${DIRLIBFT}
${PRINTF}:
	make -s -C ${DIRPRINTF}










.PHONY: all clean fclean re