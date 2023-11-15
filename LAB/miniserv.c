/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:41 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/15 21:36:53 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

char	c = 0;

void	handler_sig(int signo, siginfo_t *info, void __attribute__((unused)) *context)
{
	pid_t	senderPID;
	size_t	bit;
	char	mask;

	bit = 0;
	mask = 1;
	senderPID = info->si_pid;
	while (bit < 8)
	{
		mask = mask << bit;
		if (signo == SIGUSR1)
			bit++;
		else
		{
			c = c | mask;
			bit++;
		}
	}
	printf("char rebuilt = %c\n", c);
	kill(senderPID, SIGUSR1);
}

int	main(void)
{
	pid_t	pid;
	struct sigaction	msignal;
	
	msignal.sa_sigaction= &handler_sig;
	msignal.sa_flags = SA_SIGINFO;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
	sigaction(SIGUSR2, &msignal, 0);
	pid = getpid();
	printf("SERVER READY !\nSERVER PID [%d]\nPENDING...\n", (int)pid);
	while (1)
		pause();
	return (0);
}