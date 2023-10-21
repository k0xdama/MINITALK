/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:54 by pmateo            #+#    #+#             */
/*   Updated: 2023/10/21 18:37:11 by pmateo           ###   ########.fr       */
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

int	byte_cutting()
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
	char *message;
	
	if (argc != 3)
        return (1);
    servPID = 0;
	message = argv[3];
    servPID = (pid_t)ft_atoi(argv[1]);
	msignal.sa_handler = &handler_usr;
	msignal.sa_flags = 0;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
    
	printf("En attente d'une confirmation de reception....\n");
	pause();
    if (checking == 1)
		printf("SIGUSR1 a bien ete recu par le serveur !\n");
	return (0);
}
