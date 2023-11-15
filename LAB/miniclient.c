/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniclient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:42 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/15 21:45:20 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int	checking = 1;

static int	ft_atoi(const char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

void	send_sigusr(pid_t servPID, int choice)
{
	if (servPID <= 0)
		printf("Le PID renseigne est invalide");
	else if (choice != -1)
	{
		if (choice == 1)
			kill(servPID, SIGUSR1);
		else if (choice == 2)
			kill(servPID, SIGUSR2);
	}
	else
		printf("Echec de l'envoi d'un signal !");
}

void	cutandsend(pid_t servPID, char c)
{
	int	i;
	int	bitsent = 0;
	char mask;
	
	while(1)
	{
		i = 0;
		mask = 1;
		while(i++ < 8)
		{
			mask = mask & c;
			if (mask == 0)
			{
				send_sigusr(servPID, 1);
				printf("SIGUSR1 sent !\n");
				bitsent++;
			}
			else
			{
				send_sigusr(servPID, 2);
				printf("SIGUSR2 sent !\n");
				bitsent++;
			}
			printf("bit sent = %d\n", bitsent);
			mask = 1;
			mask = mask << i;
		}
		printf("char sent to server !\n");
		pause();
		if(checking == 42)
		{
			printf("char receveid by the server !! <3\n");
			break;
		}
	}
}

void	handler(int signo)
{
	if (signo == SIGUSR1)
		checking = 42;
}

int main(int argc, char	*argv[])
{
	pid_t servPID;
	struct sigaction	msignal;
	char	c;

	if (argc != 3)
		return (1);
	servPID = (pid_t)ft_atoi(argv[1]);
	c = *argv[2];
	msignal.sa_handler = &handler;
	msignal.sa_flags = 0;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
	cutandsend(servPID, c);
	return (0);
}