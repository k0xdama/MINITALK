/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:54 by pmateo            #+#    #+#             */
/*   Updated: 2023/10/26 01:55:41 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/client.h"

int	checking;

int	ft_atoi(const char *str)
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

void	handler_usr(int signo)
{
	if (signo == SIGUSR1)
		checking = 1;
}

void	byte_cutting(pid_t servPID, char *message)
{
	int	i;
	char c;
	char mask;
	
	while (1)
	{
		i = 0;
		c = *message;
		mask = 1;
		while (i++ < 8)
		{
			mask = mask & c;
			if (mask == 0)
				send_sigusr(servPID, 1);
			else
				send_sigusr(servPID, 2);
			mask = 1;
			mask = mask << i;
		}
		pause();
		if(!(*message))
			break;
		message++;
	}
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

int main(int argc, char *argv[])
{
    pid_t servPID;
	struct sigaction	msignal;
	
	if (argc != 3)
        return (1);
    servPID = 0;
    servPID = (pid_t)ft_atoi(argv[1]);
	msignal.sa_handler = &handler_usr;
	msignal.sa_flags = 0;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
    byte_cutting(servPID, argv[3]);
	return (0);
}
