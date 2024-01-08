/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:47:41 by pmateo            #+#    #+#             */
/*   Updated: 2024/01/08 20:16:11 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../LIBFT/INCLUDES/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

// CLIENT'S PART
void	send_sigusr(pid_t servPID, int choice);
void	cut_send(pid_t servPID, char c);
void	take_char(pid_t servPID, char *message);
// SERVER'S PART
char	add_bit(size_t	bit, char c);
void	print_and_clear(pid_t senderPID, size_t *bit, char *c);

#endif