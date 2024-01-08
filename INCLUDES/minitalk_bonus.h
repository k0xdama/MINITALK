/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:51:35 by pmateo            #+#    #+#             */
/*   Updated: 2024/01/08 20:52:59 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

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