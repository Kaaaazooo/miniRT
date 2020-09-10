/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:05:33 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:52:41 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	*v_add(t_vec *dest, t_vec *v1, t_vec *v2)
{
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;
	return (dest);
}

t_vec	*v_sub(t_vec *dest, t_vec *v1, t_vec *v2)
{
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	dest->z = v1->z - v2->z;
	return (dest);
}

t_vec	*v_mul(t_vec *dest, t_vec *v1, float m)
{
	dest->x = v1->x * m;
	dest->y = v1->y * m;
	dest->z = v1->z * m;
	return (dest);
}

t_vec	*v_div(t_vec *dest, t_vec *v1, float m)
{
	dest->x = v1->x / m;
	dest->y = v1->y / m;
	dest->z = v1->z / m;
	return (dest);
}

float	v_len(t_vec *v)
{
	return ((float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}
