/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:57 by pmateo            #+#    #+#             */
/*   Updated: 2023/10/23 20:47:02 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/server.h"

pid_t	senderPID;

void	handler_sig(int signo, siginfo_t *info, void __attribute__((unused)) *context)
{
	senderPID = info->si_pid;
	if (signo == SIGUSR1)
	{
		senderPID = info->si_pid;
		if (senderPID > 0)
			kill(senderPID, SIGUSR1);
	}
}

int	main(void)
{
	pid_t	pid;
	struct sigaction	msignal;

	senderPID = -1;
	msignal.sa_sigaction = &handler_sig;
	msignal.sa_flags = SA_SIGINFO;
	sigemptyset(&msignal.sa_mask);	
	pid = getpid();
	printf("SERVER PID : %d\n", (int)pid);
	while (1)
	{
		printf("En attente...\n");
		sigaction(SIGUSR1, &msignal, 0);
		pause();
		printf("Signal recu d'un client | PID : %d\n", (int)senderPID);
	}
	return (0);

	
}