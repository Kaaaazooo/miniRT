/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:06:09 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/25 14:35:49 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	my_rand(t_xor *state)
{
	unsigned int	x;

	x = state->a;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	state->a = x;
	return ((float)(x / ((float)UINT_MAX + 1)));
}
