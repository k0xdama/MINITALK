# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 19:28:28 by pmateo            #+#    #+#              #
#    Updated: 2023/12/04 22:13:42 by pmateo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

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
DIRPRINTF = ./PRINTF
PRINTF = ${DIRPRINTF}/libftprintf.a

${LIBFT}:
	@${MAKE} -s -C ${DIRLIBFT}
${PRINTF}:
	@${MAKE} -s -C ${DIRPRINTF}
	
${NAMECLIENT}: ${OBJCLIENT} ${LIBFT} ${PRINTF} ${INCFILES}
	${CC} ${FLAGS} -o ${NAMECLIENT} ${OBJCLIENT} -I ${DIRINC} -L ${DIRLIBFT} -L ${DIRPRINTF} -lft -lftprintf

${NAMESERVER}: ${OBJSERVER} ${LIBFT} ${PRINTF} ${INCFILES}
	${CC} ${FLAGS} -o ${NAMESERVER} ${OBJSERVER} -I ${DIRINC} -L ${DIRLIBFT} -L ${DIRPRINTF} -lft -lftprintf

${NAMECLIENT_BONUS}: ${OBJCLIENT_BONUS} ${LIBFT} ${PRINTF} ${INCFILES_BONUS}
	${CC} ${FLAGS} -o ${NAMECLIENT_BONUS} ${OBJCLIENT_BONUS} -I ${DIRINC} -L ${DIRLIBFT} -L ${DIRPRINTF} -lft -lftprintf

${NAMESERVER_BONUS}: ${OBJSERVER_BONUS} ${LIBFT} ${PRINTF} ${INCFILES_BONUS}
	${CC} ${FLAGS} -o ${NAMESERVER_BONUS} ${OBJSERVER_BONUS} -I ${DIRINC} -L ${DIRLIBFT} -L ${DIRPRINTF} -lft -lftprintf

${OBJCLIENT}: %.o: %.c ${INCFILES}
	${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT} -I ${DIRPRINTF}/INCLUDES

${OBJSERVER}: %.o: %.c ${INCFILES}
	${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT} -I ${DIRPRINTF}/INCLUDES

${OBJCLIENT_BONUS}: %.o: %.c ${INCFILES_BONUS}
	${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT} -I ${DIRPRINTF}/INCLUDES

${OBJSERVER_BONUS}: %.o: %.c ${INCFILES_BONUS}
	${CC} ${FLAGS} -o $@ -c $< -I ${DIRINC} -I ${DIRLIBFT} -I ${DIRPRINTF}/INCLUDES

all: ${NAMECLIENT} ${NAMESERVER}
		@echo "\033[1;5;35m# MANDATORY PART READY ! #\033[0m"

bonus: ${NAMECLIENT_BONUS} ${NAMESERVER_BONUS}
		@echo "\033[1;5;35m# BONUS PART READY ! #\033[0m"

clean: 
		@${MAKE} -s -C ${DIRLIBFT} clean
		@${MAKE} -s -C ${DIRPRINTF} clean
		@${RM} ${OBJCLIENT} ${OBJSERVER} ${OBJCLIENT_BONUS} ${OBJSERVER_BONUS}
		@echo "\033[1;35m# No more object files. #\033[0m"
	
fclean: clean
		@${MAKE} -s -C ${DIRLIBFT} fclean
		@${MAKE} -s -C ${DIRPRINTF} fclean
		@${RM} ${NAMECLIENT} ${NAMESERVER} ${NAMECLIENT_BONUS} ${NAMESERVER_BONUS}
		@echo "\033[1;35m# No more executable/object files. #\033[0m"
	
re: fclean all

.PHONY: all clean fclean re