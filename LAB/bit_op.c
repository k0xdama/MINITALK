/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:41:55 by pmateo            #+#    #+#             */
/*   Updated: 2023/10/23 17:21:44 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int not(int a)
{
    int res;
    printf("########### NOT OPERATEUR #############\n");
    printf("Valeur de 'a' avant modification = %d\n", a);
    res = ~a;
    return (res);
}

// int et(int a, int b)
// {
//     int res;
//     printf("########### ET OPERATEUR #############\n");
//     printf("Valeur de 'a' et 'b' : a = %d | b = %d\n", a, b);
//     res = a & b;
//     return res;
// }

// int ou(int a, int b)
// {
//     int res;
//     printf("########### OU OPERATEUR #############\n");
//     printf("Valeur de 'a' et 'b' : a = %d | b = %d\n", a, b);
//     res = a | b;
//     return res;
// }

int xor(int a, int b)
{
    int res;
    printf("######### OU EXCLUSIF OPERATEUR ##########\n");
    printf("Valeur de 'a' et 'b' : a = %d | b = %d\n", a, b);
    res = a ^ b;
    return res;
}

int shr(int value, int shifting)
{
    int res;
    printf("########## SHIFTING DROITE #########\n");
    printf("Valeur de 'value' avant shifting : a = %d\n", value);
    res = value >> shifting;
    return (res);
}

int shl(int value, int shifting)
{
    int res;
    printf("########## SHIFTING GAUCHE #########\n");
    printf("Valeur de 'value' avant shifting : a = %d\n", value);
    res = value << shifting;
    return (res);
}

int main(void)
{
    int res = 0;
    int a = 256;
    int b = 1;
    
    res = shl(a, b);
    printf("Valeur apres modification = %d\n", res);
    return (0);
}