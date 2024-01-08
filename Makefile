# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 19:28:28 by pmateo            #+#    #+#              #
#    Updated: 2024/01/08 19:26:02 by pmateo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f
.DEFAULT_GOAL := all

NAMECLIENT = client
NAMESERVER = server
NAMECLIENT_BONUS = client_bonus
NAMESERVER_BONUS = server_bonus

SRCCLIENT = SRCS/client.c 
SRCSERVER = SRCS/server.c 
SRCCLIENT_BONUS = SRCS/client_bonus.c
SRCSERVER_BONUS = SRCS/server_bonus.c

OBJCLIENT = ${SRCCLIENT:.c=.o}
OBJSERVER = ${SRCSERVER:.c=.o}
OBJCLIENT_BONUS = ${SRCCLIENT_BONUS:.c=.o}
OBJSERVER_BONUS = ${SRCSERVER_BONUS:.c=.o}

DIRINC = ./INCLUDES
INCFILES = ${DIRINC}/minitalk.h
INCFILES_BONUS = ${DIRINC}/minitalk_bonus.h

DIRLIBFT = ./LIBFT
LIBFT = ${DIRLIBFT}/libft.a

${LIBFT}:
	@${MAKE} -s -C ${DIRLIBFT}
	
${NAMECLIENT}: ${OBJCLIENT} ${LIBFT} ${INCFILES}
	@${CC} ${FLAGS} -o ${NAMECLIENT} ${OBJCLIENT} -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES -L ${DIRLIBFT} -lft 
	@echo "\033[1;5;35m# MANDATORY CLIENT'S PART READY ! #\033[0m"

${NAMESERVER}: ${OBJSERVER} ${LIBFT} ${INCFILES}
	@${CC} ${FLAGS} -o ${NAMESERVER} ${OBJSERVER} -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES -L ${DIRLIBFT} -lft
	@echo "\033[1;5;35m# MANDATORY SERVER'S PART READY ! #\033[0m"

${NAMECLIENT_BONUS}: ${OBJCLIENT_BONUS} ${LIBFT} ${INCFILES_BONUS}
	@${CC} ${FLAGS} -o ${NAMECLIENT_BONUS} ${OBJCLIENT_BONUS} -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES -L ${DIRLIBFT} -lft
	@echo "\033[1;5;35m# BONUS CLIENT'S PART READY ! #\033[0m"

${NAMESERVER_BONUS}: ${OBJSERVER_BONUS} ${LIBFT} ${INCFILES_BONUS}
	@${CC} ${FLAGS} -o ${NAMESERVER_BONUS} ${OBJSERVER_BONUS} -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES -L ${DIRLIBFT} -lft
	@echo "\033[1;5;35m# BONUS SERVER'S PART READY ! #\033[0m"

${OBJCLIENT}: %.o: %.c ${INCFILES}
	@${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES

${OBJSERVER}: %.o: %.c ${INCFILES}
	@${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES

${OBJCLIENT_BONUS}: %.o: %.c ${INCFILES_BONUS}
	@${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES

${OBJSERVER_BONUS}: %.o: %.c ${INCFILES_BONUS}
	@${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT}/INCLUDES

all: ${NAMECLIENT} ${NAMESERVER}

bonus: ${NAMECLIENT_BONUS} ${NAMESERVER_BONUS}

clean: 
		@${MAKE} -s -C ${DIRLIBFT} clean
		@${RM} ${OBJCLIENT} ${OBJSERVER} ${OBJCLIENT_BONUS} ${OBJSERVER_BONUS}
		@echo "\033[1;9;35m# No more object files. #\033[0m"
	
fclean: clean
		@${MAKE} -s -C ${DIRLIBFT} fclean
		@${RM} ${NAMECLIENT} ${NAMESERVER} ${NAMECLIENT_BONUS} ${NAMESERVER_BONUS}
		@echo "\033[1;9;35m# No more executable files. #\033[0m"
	
re: fclean all

.PHONY: all clean fclean re