/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:17:20 by pmateo            #+#    #+#             */
/*   Updated: 2023/11/15 21:27:44 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main(void)
{
    int i = 0;
    char c = 42;
    char mask = 1;
    while (i < 8)
    {
        mask = mask & c;
        printf("mask = %d\n", (int)mask);
        mask = 1;
        i++;
        mask = mask << i;
    }
}

int main(void)
{
    char c1 = '*';
    char c2 = 0;
    char mask;
    int index = 0;
    
    while(index < 8)
    {
        mask = 1;
        mask = mask << index;
        mask = mask & c1;
        if (mask != 0)
        {
          c2 = c2 | mask;
          index++;
        }
        else
          index++;
    }
}