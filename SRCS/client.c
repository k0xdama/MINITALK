/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:54 by pmateo            #+#    #+#             */
/*   Updated: 2024/01/08 20:46:05 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

int	g_checking = 0;

void	send_sigusr(pid_t servPID, int choice)
{
	if (choice == 1)
		kill(servPID, SIGUSR1);
	else if (choice == 2)
		kill(servPID, SIGUSR2);
}

void	cut_send(pid_t servPID, char c)
{
	int		bit;
	char	mask;

	bit = 0;
	mask = 1;
	while (bit < 8)
	{
		mask = mask & c;
		if (mask == 0)
			send_sigusr(servPID, 1);
		else
			send_sigusr(servPID, 2);
		bit++;
		mask = 1;
		mask = mask << bit;
		while (!g_checking)
			usleep(200);
		g_checking = 0;
	}
}

void	take_char(pid_t servPID, char *message)
{
	while (1)
	{
		cut_send(servPID, *message);
		if (!(*message))
			break ;
		message++;
	}
	ft_printf("\033[1;32m# MESSAGE SEND #\n\033[0m");
	return ;
}

void	handle_sig(int signo)
{
	if (signo == SIGUSR1)
		g_checking = 1;
	else if (signo == SIGUSR2)
	{
		ft_printf("\033[1;5;32m# MESSAGE RECEIVED BY THE SERVER <3 #\n\033[0m");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	serv_pid;

	if (argc != 3)
	{
		ft_printf("\033[1;4;33m./client <SERVER PID> \033[0m");
		ft_printf("\033[1;4;33m<MESSAGE TO SEND>\n\033[0m");
		exit(EXIT_FAILURE);
	}
	serv_pid = (pid_t)ft_atoi(argv[1]);
	if (serv_pid < 0)
	{
		ft_printf("\033[1;5;31m# INVALID PID ! #\n\033[0m");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &handle_sig);
	signal(SIGUSR2, &handle_sig);
	take_char(serv_pid, argv[2]);
	return (0);
}
