/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:57 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/04 16:20:19 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/server.h"

char	*message;

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

char	add_bit(int bit, char c, size_t index)
{
	char	mask;

	mask = 1;
	mask << index;
	if (bit == 1)
		c = c | mask;
	return (c);
}


void	handler_sig(int signo, siginfo_t *info, void __attribute__((unused)) *context)
{
	pid_t	senderPID;
	size_t	bit;
	char	c;
	char	ptrc[1];
	
	senderPID = info->si_pid;
	bit = 0;
	ptrc[1] = '\0';
	while (1)
	{
		while (bit++ != 8)
		{
			if (signo == SIGUSR1)
				c = add_bit(0, c, bit);
			else if (signo == SIGUSR2)
				c = add_bit(1, c, bit);
		}
		ptrc[0] = c;
		if (ptrc[0] == 0)
			break;
		message = ft_strjoin(message, ptrc);
	}
}

int	main(void)
{
	pid_t	pid;
	struct sigaction	msignal;

	msignal.sa_sigaction = &handler_sig;
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