/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:59:57 by pmateo            #+#    #+#             */
/*   Updated: 2023/10/16 20:27:30 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handler(int signb)
{
	
}

void	server()
{
	pause();
	

}

int	main(void)
{
	pid_t	pid;
	struct sigaction	managSignal;

	
	
	managSignal.sa_handler = &handler;
	managSignal.sa_flags = 0;
	sigemptyset(&managSignal.sa_mask);	
	pid = getpid();
	printf("SERVER PID : %d", (int)pid);
	server();
	
	
}