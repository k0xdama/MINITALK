/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:57 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/27 21:18:15 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

char	*message;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	size_t			size;
	char			*str;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(size * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

static char	add_bit(char c, size_t bit)
{
	char	mask;

	mask = 1;
	mask = mask << bit;
	c = c | mask;
	return (c);
}


void	handler_sig(int signo, siginfo_t *info, void __attribute__((unused)) *context)
{
	pid_t	senderPID;
	static size_t	bit;
	static char	c;
	static char	ptrc[2];
	
	senderPID = info->si_pid;
	ptrc[1] = '\0';
	if (bit < 8)
	{
		if (signo == SIGUSR1)
			bit++;
		else if (signo == SIGUSR2)
		{
			c = add_bit(c, bit);
			bit++;
		}
		kill(senderPID, SIGUSR1);
	}
	if (bit == 8 && c)
	{
		ptrc[0] = c;
		message = ft_strjoin(message, ptrc);
		bit = 0;
		c = 0;
	}
	else if (bit == 8 && !c)
	{
		kill(senderPID, SIGUSR2);
		printf("CLIENT'S MESSAGE : < %s >\n", message);
	}
}

int	main(void)
{
	pid_t	pid;
	struct sigaction	msignal;

	message = malloc(sizeof(char));
	message[0] = '\0';
	msignal.sa_sigaction = &handler_sig;
	msignal.sa_flags = SA_SIGINFO;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
	sigaction(SIGUSR2, &msignal, 0);
	pid = getpid();
	printf("SERVER READY !\nSERVER PID [%d]\nPENDING...\n", (int)pid);
	while (1)
		pause();
	free(message);
	return (0);
}