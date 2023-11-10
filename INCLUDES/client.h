/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:30:12 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/10 15:21:28 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

// int		ft_atoi(const char *str);
void	handler_usr(int signo);
void	byte_cutting(pid_t servPID, char *message);
void	send_sigusr(pid_t servPID, int choice);


























#endif