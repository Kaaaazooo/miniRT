/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:06:09 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/24 16:44:20 by sabrugie         ###   ########.fr       */
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

float	get_t(float t1, float t2)
{
	float		min;

	min = 0.001;
	if (t1 <= min && t2 <= min)
		return (0);
	if (t1 <= min)
		return (t2);
	if (t2 <= min)
		return (t1);
	return (t1 < t2 ? t1 : t2);
}
