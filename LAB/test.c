/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:17:20 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/27 03:12:27 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// int main(void)
// {
//     int i = 0;
//     char c = 42;
//     char mask = 1;
//     while (i < 8)
//     {
//         mask = mask & c;
//         printf("mask = %d\n", (int)mask);
//         mask = 1;
//         i++;
//         mask = mask << i;
//     }
// }

// int main(void)
// {
//     char c1 = '*';
//     char c2 = 0;
//     char mask;
//     int index = 0;
    
//     while(index < 8)
//     {
//         mask = 1;
//         mask = mask << index;
//         mask = mask & c1;
//         if (mask != 0)
//         {
//           c2 = c2 | mask;
//           index++;
//         }
//         else
//           index++;
//     }
// }

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(void)
{
	// char c = 42;
	// char c1 = 233;
	// char c2 = -23;
	// char c3 = 0xE9;
	// char c4 = 142;
	// printf("%c\n%c\n%c\n%c\n%c\n", c, c1, c2, c3, c4);
	char *utf8 = "école";
	size_t	ret = 0;
	ret = ft_strlen(utf8);
	printf("%ld\n", ret);
}