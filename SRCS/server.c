/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:57 by pmateo            #+#    #+#             */
/*   Updated: 2024/01/08 20:45:24 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

char	*g_message;

char	add_bit(size_t	bit, char c)
{
	char	mask;

	mask = 1;
	mask <<= bit;
	c = c | mask;
	return (c);
}

void	print_and_clear(pid_t senderpid, size_t *bit, char *c)
{
	kill(senderpid, SIGUSR2);
	ft_printf("CLIENT'S MESSAGE : < %s >\n", g_message);
	free(g_message);
	g_message = NULL;
	g_message = ft_calloc(1, 1);
	*bit = 0;
	*c = 0;
}

void	handler_sig(int signo, siginfo_t *info, void *context)
{
	pid_t			senderpid;
	static size_t	bit;
	static char		c;
	char			*tmp;

	(void)context;
	senderpid = info->si_pid;
	if (bit < 8)
	{
		if (signo == SIGUSR2)
			c = add_bit(bit, c);
		bit++;
	}
	if (bit == 8 && c)
	{
		tmp = g_message;
		g_message = ft_strjoin(g_message, &c);
		free(tmp);
		tmp = NULL;
		bit = 0;
		c = 0;
	}
	else if (bit == 8 && !c)
		print_and_clear(senderpid, &bit, &c);
	kill(senderpid, SIGUSR1);
}

void	sigint_exit(int signo)
{
	if (signo == SIGINT)
	{
		free(g_message);
		g_message = NULL;
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char __attribute__((unused)) *argv[])
{
	pid_t				pid;
	struct sigaction	msignal;

	if (argc != 1)
	{
		ft_printf("\033[1;31m#THIS PROGRAM REQUIRES NO ARGUMENTS ! #\n\033[0m");
		exit(EXIT_FAILURE);
	}
	msignal.sa_sigaction = &handler_sig;
	msignal.sa_flags = SA_SIGINFO;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
	sigaction(SIGUSR2, &msignal, 0);
	signal(SIGINT, &sigint_exit);
	g_message = ft_calloc(1, 1);
	pid = getpid();
	ft_printf("\033[1;34mSERVER READY !\n");
	ft_printf("\033[1;34mSERVER PID [%d]\nPENDING...\n\033[0m", (int)pid);
	while (1)
		pause();
	return (0);
}
