/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:57 by pmateo            #+#    #+#             */
/*   Updated: 2023/12/18 20:33:33 by pmateo           ###   ########.fr       */
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

void	*ft_calloc(size_t num, size_t size)
{
	void	*buffer;
	size_t	i;
	size_t	tmp;

	i = 0;
	if (num == 0 || size == 0)
	{
		num = 1;
		size = 1;
	}
	tmp = num * size;
	if ((tmp / size) != num)
		return (NULL);
	buffer = (void *)malloc(size * num);
	if (!buffer)
		return (NULL);
	while (i < num * size)
	{
		((unsigned char *)buffer)[i] = 0;
		i++;
	}
	return (buffer);
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

void	join_char(char *message, size_t *bit, char *c)
{
	char *tmp;
	char	ptrc[2];

	ptrc[0] = *c;
	ptrc[1] = '\0';
	tmp = message;
	message = ft_strjoin(message, ptrc);
	free(tmp);
	tmp = NULL;
	*bit = 0;
	*c = 0;
}

char	add_bit(size_t	bit, char c)
{
	char	mask;

	mask = 1;
	mask <<= bit;
	c = c | mask;
	return (c);
}

void	print_and_clear(pid_t senderPID, size_t *bit, char *c)
{
	kill(senderPID, SIGUSR2);
	printf("CLIENT'S MESSAGE : < %s >\n", message);
	free(message);
	message = ft_calloc(1, 1);
	*bit = 0;
	*c = 0;
}

void	handler_sig(int signo, siginfo_t *info, void *context)
{
	pid_t	senderPID;
	static size_t	bit;
	static char	c;
	char	*tmp;
	
	(void)context;
	senderPID = info->si_pid;
	if (bit < 8)
	{
		if (signo == SIGUSR2)
			add_bit(bit, c);
		bit++;
		kill(senderPID, SIGUSR1);
	}
	printf("c = %c\n", c);
	if (bit == 8 && c)
	{
		tmp = message;
		message = ft_strjoin(message, &c);
		free(tmp);
		tmp = NULL;
		bit = 0;
		c = 0;
	}
	else if (bit == 8 && !c)
		print_and_clear(senderPID, &bit, &c);
}

void	sigint_exit(int signo)
{
	if (signo == SIGINT)
	{
		free(message);
		message = NULL;
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char __attribute__((unused)) *argv[])
{
	pid_t	pid;
	struct sigaction	msignal;

	if (argc != 1)
	{
		printf("### THIS PROGRAM REQUIRES NO ARGUMENTS ! ###\n");
		exit(EXIT_FAILURE);
	}
	msignal.sa_sigaction = &handler_sig;
	msignal.sa_flags = SA_SIGINFO;
	sigemptyset(&msignal.sa_mask);
	sigaction(SIGUSR1, &msignal, 0);
	sigaction(SIGUSR2, &msignal, 0);
	signal(SIGINT, &sigint_exit);
	message = ft_calloc(1, 1);
	pid = getpid();
	printf("SERVER READY !\nSERVER PID [%d]\nPENDING...\n", (int)pid);
	while (1)
		pause();
	return (0);
}