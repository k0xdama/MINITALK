/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:54 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/27 03:26:59 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/client.h"

int	checking = 0;

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

static char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

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



void	cut_send(pid_t servPID, char c)
{
	int	i;
	char mask;
	
	i = 7;
	mask = 1;
	while (i >= 0)
	{
		mask = mask & c;
		if (mask == 0)
		{
			send_sigusr(servPID, 1);
			printf("SIGUSR1 sent !\n");			}
		else
		{
			send_sigusr(servPID, 2);
			printf("SIGUSR2 sent !\n");
		}
		printf("byte sent = %d\n", i;
		i--;
		mask = 1;
		mask = mask << i;
		while (checking != 1)
			pause();
		checking = 0;
	}
}

void	take_char(pid_t servPID, char *message)
{
	while(message)
	{
		cut_send(servPID, *message);
		message++;
	}
	printf("MESSAGE SEND\n");
	return;
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

void	handle_sigusr(int signo)
{
	if(signo == SIGUSR1)
		checking = 1;
	else
		printf("MESSAGE RECEIVED BY THE SERVER <3\n");
}

int main(int argc, char *argv[])
{
    pid_t servPID;
	char	*message;
	
	if (argc != 3)
        return (1);
    servPID = (pid_t)ft_atoi(argv[1]);
	message = ft_strdup(argv[2]);
	checking = 1;
	printf("MESSAGE < %s >\n", message);
	signal(SIGUSR1, )
    byte_cutting(servPID, message);
	return (0);
}
