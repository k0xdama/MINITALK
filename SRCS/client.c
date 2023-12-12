/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:54 by pmateo            #+#    #+#             */
/*   Updated: 2023/12/12 19:24:48 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

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

	if (s1 == NULL)
		return (NULL); // a corriger dans LIBFT
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

static	void	send_sigusr(pid_t servPID, int choice)
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

static	void	cut_send(pid_t servPID, char c)
{
	int	bit;
	char mask;
	
	bit = 0;
	mask = 1;
	while (bit < 8)
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
		printf("bit index = %d\n", bit);
		bit++;
		mask = 1;
		mask = mask << bit;
		while (checking != 1)
			pause();
		checking = 0;
	}
}

static	void	take_char(pid_t servPID, char *message)
{
	while(1)
	{
		cut_send(servPID, *message);
		if (!(*message))
			break;
		message++;
	}
	printf("MESSAGE SEND\n");
	return;
}

void	handle_sig(int signo)
{
	if (signo == SIGUSR1)
		checking = 1;
	else if (signo == SIGUSR2)
		printf("MESSAGE RECEIVED BY THE SERVER <3\n");
	else if (signo == SIGINT)
	{
		free(message);
		
	}
}

int main(int argc, char *argv[])
{
    pid_t servPID;
	char	*message;
	
	if (argc != 3)
        return (1);
    servPID = (pid_t)ft_atoi(argv[1]);
	message = ft_strdup(argv[2]);
	printf("MESSAGE < %s >\n", message);
	signal(SIGUSR1, &handle_sig);
	signal(SIGUSR2, &handle_sig);
	signal(SIGINT, &handle_sig);
    take_char(servPID, message);
	free(message);
	message = NULL;
	return (0);
}
