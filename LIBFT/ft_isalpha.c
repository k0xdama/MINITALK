/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:51:44 by pmateo            #+#    #+#             */
/*   Updated: 2023/05/05 20:43:28 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	char	c;

	c = -1;
	printf("ma fonction retourne %d\n", ft_isalpha(c));
	printf("la fonction de base retourne %d", isalpha(c));
}*/
