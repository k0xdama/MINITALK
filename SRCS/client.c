/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:54 by pmateo            #+#    #+#             */
/*   Updated: 2023/10/19 19:46:54 by pmateo           ###   ########.fr       */
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

void	handler_usr1(int signo)
{
	if (signo == SIGUSR1)
		checking = 1;
}

int main(int argc, char *argv[])
{
    int servPID;
	struct sigaction	msignal;
	

    servPID = 0;
	checking = 0;
    if (argc != 2)
        return (1);
    servPID = ft_atoi(argv[1]);
	msignal.sa_handler = &handler_usr1;
	msignal.sa_flags = 0;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
    if (servPID <= 0)
        printf("Le PID renseigne est invalide\n");
	else
	{
        kill(servPID, SIGUSR1);
		printf("Signal envoye...\n");
	}
	printf("En attente d'une confirmation de reception....\n");
	pause();
    if (checking == 1)
		printf("SIGUSR1 a bien ete recu par le serveur !\n");
	return (0);
}
